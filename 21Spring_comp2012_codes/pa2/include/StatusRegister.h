#ifndef STATUS_REGISTER_H
#define STATUS_REGISTER_H

/**
 * \brief Processor Status Register.
 *
 * This register is called APSR (Application Program Status Register) in ARM. This register is used to determine whether
 * conditional instructions are executed.
 */
struct StatusRegister {
  bool mN;
  bool mZ;
  bool mC;
  bool mV;

  bool mT;
};

#endif  // STATUS_REGISTER_H
