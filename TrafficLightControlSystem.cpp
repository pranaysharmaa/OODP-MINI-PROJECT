#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

const int MAX_NUM_LANES = 4;
const int MIN_VEHICLE_DENSITY = 0;
const int MAX_VEHICLE_DENSITY = 200;
const int MAX_PHASE_DURATION = 60;
const int MIN_GREEN_DURATION = 10;
const int MAX_GREEN_DURATION = 45;

struct Lane {
  int id; // Lane ID
  int vehicle_density; // Current vehicle density
  int green_duration; // Current green phase duration
};

class TrafficLightControlSystem {
public:
  TrafficLightControlSystem() {
    // Initialize the lanes
    lanes_ = std::vector<Lane>(MAX_NUM_LANES);
    for (int i = 0; i < MAX_NUM_LANES; ++i) {
      lanes_[i].id = i;
      lanes_[i].vehicle_density = 0;
      lanes_[i].green_duration = 0;
    }

    // Initialize the traffic light phase duration
    phase_duration_ = MAX_PHASE_DURATION;
  }

  // Update the vehicle density for a lane
  void updateVehicleDensity(int lane_id, int vehicle_density) {
    if (lane_id >= 0 && lane_id < MAX_NUM_LANES) {
      lanes_[lane_id].vehicle_density = vehicle_density;
    }
  }

  // Get the current green duration for a lane
  int getGreenDuration(int lane_id) const {
    if (lane_id >= 0 && lane_id < MAX_NUM_LANES) {
      return lanes_[lane_id].green_duration;
    }
    return 0;
  }

  // Get the current phase duration
  int getPhaseDuration() const {
    return phase_duration_;
  }

  // Update the traffic light phase
  void updatePhase(bool emergency_vehicle_present) {
    if (emergency_vehicle_present) {
      // If an emergency vehicle is present, set the phase duration to the minimum
      phase_duration_ = MIN_GREEN_DURATION;
      for (auto& lane : lanes_) {
        lane.green_duration = MIN_GREEN_DURATION;
      }
    } else {
      // Determine the lane with the highest vehicle density
      int max_vehicle_density = MIN_VEHICLE_DENSITY;
      int max_vehicle_density_lane = -1;
      for (int i = 0; i < MAX_NUM_LANES; ++i) {
        if (lanes_[i].vehicle_density > max_vehicle_density) {
          max_vehicle_density = lanes_[i].vehicle_density;
          max_vehicle_density_lane = i;
        }
      }

      // Calculate the green duration for each lane based on its vehicle density
      int total_green_duration = 0;
      for (int i = 0; i < MAX_NUM_LANES; ++i) {
        if (i == max_vehicle_density_lane) {
          lanes_[i].green_duration = MAX_GREEN_DURATION;
        } else {
          lanes_[i].green_duration = MIN_GREEN_DURATION;
        }
        total_green_duration += lanes_[i].green_duration;
      }

      // Calculate the phase duration based on the total green duration
      phase_duration_ = std::min(total_green_duration * 2, MAX_PHASE_DURATION);
    }
  }

private:
  std::vector<Lane> lanes_; // The lanes
  int phase_duration_; // The current phase duration
};

int main() {
  TrafficLightControlSystem tlcs;

  // Simulate the traffic light control system
  while (true) {
    // Assume that the RFID reader detects whether an emergency vehicle is present
    bool emergency_vehicle_present = (rand() % 100) < 5;

    // Update the vehicle density for each lane
    for (int i = 0; i < MAX_NUM_LANES; ++i) {
      int vehicle_density = rand() % (MAX_VEHICLE_DENSITY + 1);
      tlcs.updateVehicleDensity(i, vehicle_density);
    }

    // Update the traffic light phase
    tlcs.updatePhase(emergency_vehicle_present);

    // Print the current phase duration and green duration for each lane
    std::cout << "Phase duration: " << tlcs.getPhaseDuration() << std::endl;
    for (int i = 0; i < MAX_NUM_LANES; ++i) {
      std::cout << "Lane " << i << " green duration: " << tlcs.getGreenDuration(i) << std::endl;
    }

    // Wait for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
