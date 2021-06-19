// Name: YANG Jingwen
// SID: 20677029
#include "smart_storage.h"

using namespace std;

// During ZINC grading, TA will provide some of his code to help you achieve the goal.
// For example, when grading the function select_container_for_buyer, TA will provide his code of deselect_container.
// This allows you to get points even without the implementation of deselect_container.
// However, there are some drawbacks as TA's code may not be compatible with yours, and you may fail in some cases.
// Therefore, if you are confident with your implementation and don't want TA to help you,
// uncomment the following line (make sure there is no space before '#'):
// #define PLEASE_DONT_HELP_ME

// You can define the following helper functions.
// Note that they are optional. If you don't need them, just delete them.
// They are just hints for your reference and the grader won't check them.

// Helper functions begin.

int num_children(const SmartContainer *p)
{
    // Return the number of children given a smart container.
    if (p->left == nullptr && p->right == nullptr) return 0;
    else if (p->left != nullptr && p->right != nullptr) return 2;
    else return 1;
}

int get_subtree_height(SmartContainer* root)
{
    if (root == nullptr) return -1;
    int left_height = get_subtree_height(root->left);
    int right_height = get_subtree_height(root->right);
    int subtree_height = (left_height > right_height) ? left_height : right_height;
    return subtree_height + 1;
}

bool on_tree(SmartContainer *p)
{
    // Return true if the container is on a BST else false.
    if (p->parent == nullptr && p->left == nullptr && p->right == nullptr) return false;
    else return true;
}

SmartContainer *&get_first_child(SmartContainer *p)
{
    // Return a reference to the first non-null child pointer.
    // If it does not have a non-null child pointer,
    // just return either of the null child pointer.
    if (p->left != nullptr) return p->left;
    else if (p->right != nullptr) return p->right;
    else return p->left;
}

SmartContainer *find_root(const vector<Container *> &containers, Container *ignored = nullptr)
{
    // Find the root from the containers.
    // Ignore the 'ignored' container to avoid treating the node to be inserted as the root.
    for (unsigned long int i = 0; i < containers.size(); i++){
        if (containers[i] == nullptr || containers[i] == ignored || containers[i]->empty()) continue;
        if (dynamic_cast<SmartContainer *>(containers[i])->parent == nullptr) return dynamic_cast<SmartContainer *>(containers[i]);
    }
    return nullptr;
}

SmartContainer *find_just_heavier(SmartContainer *root, const SmartContainer *reference)
{
    SmartContainer *comparenode = root;
    SmartContainer *returnnode = nullptr;
    bool found = false;

    if (root == nullptr) return nullptr; // special case: empty tree
    if (reference->empty()){ // special case: empty reference
        returnnode = root;
        while (returnnode->left != nullptr) returnnode = returnnode->left;
        return returnnode;
    }
    
    while (!found){
        if (!(*reference < *comparenode)){ // comparenode lighter than or equal to reference
            if (comparenode->right != nullptr) comparenode = comparenode->right;
            else found = true;
        }
        else{ // comparenode heavier than reference
            returnnode = comparenode;
            if (comparenode->left != nullptr) comparenode = comparenode->left;
            else found = true;
        }
    }

    return returnnode;
}

SmartContainer *find_replace_node(SmartContainer * node)
{
    SmartContainer *returnnode = nullptr;
    if (get_subtree_height(node->left) > get_subtree_height(node->right)){ // find maximum on leftsubtree
        if (node->left != nullptr) returnnode = node->left;
        while (returnnode->right != nullptr) returnnode = returnnode->right;
    }
    else{ // find minimum on rightsubtree
        if (node->right != nullptr) returnnode = node->right;
        while (returnnode->left != nullptr) returnnode = returnnode->left;
    }
    return returnnode;
}

void insert_node(SmartContainer *root, SmartContainer *node)
{
    // Insert a node to the BST given its root.
    if (node->empty()) return; // special case: empty node
    if (root == nullptr){ // special case: empty tree, assign node to root
        root = node;
        return;
    }

    SmartContainer *comparenode = root;
    while (true){
        if (*comparenode < *node){ // comparenode lighter than node, goto rightsubtree
            if (comparenode->right != nullptr) comparenode = comparenode->right;
            else{
                comparenode->right = node;
                node->parent = comparenode;
                break;
            }
        }
        else{ // comparenode heavier than node, goto leftsubtree
            if (comparenode->left != nullptr) comparenode = comparenode->left;
            else{
                comparenode->left = node;
                node->parent = comparenode;
                break;
            }
        }
    }
}

void detach_node(SmartContainer *node)
{
    // Detach (delete, without destruction though) a node from the BST given the node.
    if(node->parent == nullptr){ // special case: node is the root
        SmartContainer *newroot = find_replace_node(node);
        detach_node(newroot);
        newroot->left = node->left;
        newroot->right = node->right;
        if(newroot->right != nullptr) newroot->right->parent = newroot;
        if(newroot->left != nullptr) newroot->left->parent = newroot;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        return;
    }
    
    if (num_children(node) == 0){
        if (node->parent->left == node) node->parent->left = nullptr;
        else if (node->parent->right == node) node->parent->right = nullptr;
        node->parent = nullptr;
    }
    else if(num_children(node) == 1){
        get_first_child(node)->parent = node->parent;
        if (node->parent->left == node) node->parent->left = get_first_child(node);
        else if (node->parent->right == node) node->parent->right = get_first_child(node);
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
    }
    else if(num_children(node) == 2){
        SmartContainer *replacenode = find_replace_node(node); 
        detach_node(replacenode);

        if (node->parent->left == node) node->parent->left = replacenode;
        else if (node->parent->right == node) node->parent->right = replacenode;

        replacenode->left = node->left;
        replacenode->right = node->right;
        replacenode->parent = node->parent;
        if(replacenode->right != nullptr) replacenode->right->parent = replacenode;
        if(replacenode->left != nullptr) replacenode->left->parent = replacenode;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
    }
}

// Helper functions end.

void SmartStorage::select_container_for_buyer()
{
    // An example implementation of select_container_for_buyer is given below for your reference:

    SmartContainer *downcasted_reference = dynamic_cast<SmartContainer *>(reference);
    // Select the container containing the cheapest gem for the buyer.
    // If the reference container contains a gem from the customer, find a heavier gem.
    selected = find_just_heavier(find_root(containers), downcasted_reference);
}

void SmartStorage::deselect_container()
{
    // An example implementation of deselect_container is given below for your reference:

    if (selected != nullptr)
    {
        SmartContainer *downcasted_selected = dynamic_cast<SmartContainer *>(selected);
        //cout << downcasted_selected->empty() << " " << on_tree(downcasted_selected)<< endl;
        //cout << (downcasted_selected->parent==nullptr) <<" "<< (downcasted_selected->left==nullptr)<<" "<<(downcasted_selected->right==nullptr)<<endl;
        // As the customer may have changed the content of the selected container, the structure of the BST has to be changed here.
        // If a buyer bought the gem away, then the empty selected container should be removed from the BST.
        // On the other hand, if a seller sold a gem, the new non-empty container should be put on the BST.
        // Hint: You don't have to put the first non-empty container onto the BST.
        if (!downcasted_selected->empty() && !on_tree(downcasted_selected))
        {
            // The selected container is not empty but it's not on the BST.
            // The customer may have sold us a gem.
            // Attach the selected container on the BST.

            // Find the root, note that don't mistake the selected one as the root.
            // Then insert the selected node on the BST.
            insert_node(find_root(containers, selected), downcasted_selected);
        }
        else if (downcasted_selected->empty() && on_tree(downcasted_selected))
        {
            // The selected container is empty.
            // The customer may have bought the gem away.
            // Detach the selected container from the BST.
            detach_node(downcasted_selected);
        }

        // Don't forget to deselect!
        selected = nullptr;
    }
}
