#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;
  
  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  bool twiddle = false;
  double p[3] = {0.05, 0.0001, 1.5};
  double dp[3] = {0.01, 0.0001, 0.1};
  double best_p[3] = {p[0],p[1],p[2]};
  
  int i = 0;
  int max_iteration = 600;
  
  double total_cte = 0.0;
  double error = 0.0;
  double best_error = 10000.00;
  double tolerance = 0.001;
  
  int p_iterator = 0;
  int total_iterator = 0;
  int sub_move = 0; //indicator to change to the next parameter in p to optimize
  bool first = true; //first twiddle to increment the gain (p[p_iterator] += dp[p_iterator])
  bool second = true; //second twiddle to decrement the gain twice (p[p_iterator] -= 2 * dp[p_iterator];)
  
  
  if(twiddle == true) {
    pid.Init(p[0],p[1],p[2]);
  }
  else{
    //pid.Init(0.06,0.00031,1.29);
    pid.Init(0.308691, 0.00113215, 2.86725);
  }
  
  

  h.onMessage([&pid, &p, &dp, &best_p, &i, &max_iteration, &total_cte, &error, &best_error, &tolerance, 
               &p_iterator, &total_iterator, &sub_move, &first, &second, &twiddle](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          //double speed = std::stod(j[1]["speed"].get<string>());
          //double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          double throttle_value = 0.3;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          
          json msgJson;
          
          if (twiddle == true){
            total_cte = total_cte + pow(cte,2);
            
            
            if(i==0){
              pid.Init(p[0],p[1],p[2]);
            }
            
            pid.UpdateError(cte);
            steer_value = pid.TotalError();
            // DEBUG
            //std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;
            
            i = i+1;
            if (i > max_iteration){ 
             if(first == true) { 
                std::cout << "Intermediate p[0] p[1] p[2]: " << p[0] << " " << p[1] << " " << p[2] << "\n";
                p[p_iterator] += dp[p_iterator];
                first = false;
             }
             else{
                error = total_cte/max_iteration;        
                if(error < best_error && second == true) {
                  best_error = error;
                    best_p[0] = p[0];
                    best_p[1] = p[1];
                    best_p[2] = p[2];
                    dp[p_iterator] *= 1.1;
                    sub_move += 1;
                    std::cout << "iteration: " << total_iterator << "\n";
                    std::cout << "p_iterator: " << p_iterator << "\n";
                    std::cout << "p[0] p[1] p[2]: " << p[0] << " " << p[1] << " " << p[2] << "\n";
                    std::cout << "error: " << error << "\n";
                    std::cout << "best_error: " << best_error << "\n";
                    std::cout << "Best p[0] p[1] p[2]: " << best_p[0] << " " << best_p[1] << " " << best_p[2] << "\n";
                    std::cout << "dp[0] dp[1] dp[2]: " << dp[0] << " " << dp[1] << " " << dp[2] << "\n";
                }
                else{
                  if(second == true) {
                    std::cout << "Intermediate p[0] p[1] p[2]: " << p[0] << " " << p[1] << " " << p[2] << "\n";
                    p[p_iterator] -= 2 * dp[p_iterator];
                    second = false;
                  }
                  else{
                    std::cout << "iteration: " << total_iterator << "\n";
                    std::cout << "p_iterator: " << p_iterator << "\n";
                    std::cout << "p[0] p[1] p[2]: " << p[0] << " " << p[1] << " " << p[2] << "\n";
                    if(error < best_error) {
                        best_error = error;
                        best_p[0] = p[0];
                        best_p[1] = p[1];
                        best_p[2] = p[2];
                        dp[p_iterator] *= 1.1;
                        sub_move += 1;
                    }else {
                        p[p_iterator] += dp[p_iterator];
                        dp[p_iterator] *= 0.9;
                        sub_move += 1;
                    }
                    std::cout << "error: " << error << "\n";
                    std::cout << "best_error: " << best_error << "\n";
                    std::cout << "Best p[0] p[1] p[2]: " << best_p[0] << " " << best_p[1] << " " << best_p[2] << "\n";
                    std::cout << "dp[0] dp[1] dp[2]: " << dp[0] << " " << dp[1] << " " << dp[2] << "\n";
                  }
                  
                }
              }
              
             if(sub_move > 0) {
                p_iterator = p_iterator+1;
                first = true;
                second = true;
                sub_move = 0;
              }
              
             if(p_iterator == 3) {
                p_iterator = 0;
              }
              
             total_cte = 0.0;
             i = 0;
             total_iterator = total_iterator+1;
              
             double sumdp = dp[0]+dp[1]+dp[2];
             if(sumdp < tolerance) {
               std::cout << "Best p[0] p[1] p[2]: " << best_p[0] << best_p[1] << best_p[2] << "\n";
               std::cout << "dp[0] dp[1] dp[2]: " << dp[0] << " " << dp[1] << " " << dp[2] << "\n";
               //ws.close();
               //std::cout << "Disconnected" << std::endl;
             } 
             else {
               std::cout << "RESET !! (sumdp > tolerance)" << "\n";
               std::string reset_msg = "42[\"reset\",{}]";
               ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
             }
            }
            else{
              msgJson["steering_angle"] = steer_value;
              msgJson["throttle"] = throttle_value;
              auto msg = "42[\"steer\"," + msgJson.dump() + "]";
              ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
          } //end "twiddle" if
          else{ 
            pid.UpdateError(cte);
            steer_value = pid.TotalError();
        
            // DEBUG
            std::cout << "CTE: " << cte << " Steering Value: " << steer_value << " Throttle Value: " << throttle_value << " Count: " << i << std::endl;
            msgJson["steering_angle"] = steer_value;
            msgJson["throttle"] = throttle_value;
            auto msg = "42[\"steer\"," + msgJson.dump() + "]";
            std::cout << msg << std::endl;
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          } // end "twiddle" else
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}