#include <iostream>

#include "database/database.h"
#include "utils/Address.h"
#include "utils/Car.h"
#include "utils/Driver.h"
#include "utils/Passenger.h"
#include "utils/PaymentMethods.h"
#include "utils/Ride.h"
#include "utils/System.h"

using namespace std;

int main() {
  auto drivers = database::get_drivers();
  auto passengers = database::get_passengers();
  auto pending_rides = database::get_rides_pending();
  auto completed_rides = database::get_rides_complete();

  auto main_system =
      new Gateway(drivers, passengers, pending_rides, completed_rides);

  auto passenger_gateway = PassengerGateway(main_system);
  auto drivers_gateway = DriverGateway(main_system);

  auto pas1 = passengers[0];

  // We request a ride which will be found a bit later
  passenger_gateway.add_ride(new Ride(pas1->create_order(
      Address("point1"), Address("point2"), car::CarType::Economy, 0)));

  auto driver1 = drivers[0];
  auto current_ride =
      driver1->choose_order(drivers_gateway.get_available_rides());

  // Current ride will be nullptr if there are no rides for this driver
  if (current_ride != nullptr) {
    // This branch will one more line to "rides_completed.csv" file
    // Because there is a driver who will accept it
    drivers_gateway.take_ride(current_ride, driver1);

    auto result = passenger_gateway.ask_for_special_parking(current_ride);
    // Result will be zero, because it is not Business class
    cout << "Result of request for special parking: " << result << endl;

    auto coords = passenger_gateway.get_current_coordinates(current_ride);
    cout << "Result of request for coordinates: " << coords << endl;

    // From ride to ride you can see in row with business car, that number of
    // bottles decreases
    drivers_gateway.complete_ride(current_ride);
  }

  // This will add one more line to pending orders in "riders_pending.csv"
  // Because there are no drivers with ComfortPlus car
  passenger_gateway.add_ride(new Ride(pas1->create_order(
      Address("point1"), Address("point2"), car::CarType::ComfortPlus, 0)));

  // Business driver
  auto driver2 = drivers[1];

  // Example of creating new ride with pinned address, and Business type
  passenger_gateway.add_ride(new Ride(
      pas1->create_order(Address("point1"), *pas1->get_pinned_addresses()[0],
                         car::CarType::Business, 0)));

  auto current_ride_business =
      driver2->choose_order(drivers_gateway.get_available_rides());
  if (current_ride_business != nullptr) {
    drivers_gateway.take_ride(current_ride_business, driver2);

    auto result =
        passenger_gateway.ask_for_special_parking(current_ride_business);
    // Result will be one, because it is Business class
    cout << "Result of request for special parking: " << result << endl;

    auto coords =
        passenger_gateway.get_current_coordinates(current_ride_business);
    cout << "Result of request for coordinates: " << coords << endl;

    drivers_gateway.complete_ride(current_ride_business);
  }

  auto history_of_first_passenger = pas1->get_order_history();
  // History will increase in size after each run
  cout << "HISTORY OF FIRST PASSENGER" << endl;
  for (auto order : history_of_first_passenger) {
    cout << order->get_output_format() << endl;
  }

  auto pas2 = passengers[1];

  // You will see increasing of number of available payment options for second
  // passenger in database
  pas2->add_payment_method(
      new payment::Payment(payment::PaymentMethod::CARD, 0));

  // This will not add a new pending ride in database, because user had not
  // enough money in his cash
  passenger_gateway.add_ride(new Ride(pas2->create_order(
      Address("retake1"), Address("retake2"), car::CarType::Business, 0)));

  database::load_drivers(drivers);
  database::load_passengers(passengers);
  database::load_rides_completed(main_system->rides_completed);
  database::load_rides_pending(main_system->rides_pending);
}