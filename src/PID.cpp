#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  this->Kp = Kp_;
  this->Ki = Ki_;
  this->Kd = Kd_;
  this->i_error = 0.0;
  this->p_error = 0.0;
  this->d_error = 0.0;
  this->prev_cte = 0.0;

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  this->prev_cte = this->p_error;
  this->p_error = cte;
  this->d_error = this->p_error - this->prev_cte;
  this->i_error += this->p_error;
  
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  
  // TODO: Add your total error calc here!
  return (-Kp * p_error) - (Kd * d_error) - (Ki * i_error);
}