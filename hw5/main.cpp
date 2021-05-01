#include <iostream>

#include "database/database.h"
#include "utils/Address.h"
#include "utils/Admin.h"
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
  auto permissions = database::get_permissions();
  auto admins = database::get_admins();

  auto main_system = new Gateway(drivers, passengers, pending_rides,
                                 completed_rides, permissions, admins);

  auto passenger_gateway = PassengerGateway(main_system);
  auto drivers_gateway = DriverGateway(main_system);
  auto admin_gateway = AdminGateway(main_system);

  // login of admin
  auto admin1 = admin::login(admins, 0);

  // login of passenger
  auto passenger1 = login(passengers, 0);

  // login of driver
  auto driver1 = driver::login(drivers, 1);

  // selecting the car which is not validated
  driver1->select_car(0);
  try {
    auto order = driver1->choose_order(drivers_gateway.get_available_rides());
  } catch (car::CarNotValidated e) {
    cout << "Car was not validated and I catched the exception" << endl;
  }

  // this car is validated
  driver1->select_car(1);

  // removing ability to take a ride for Dinar (driver)
  admin_gateway.update_permission(admin1->set_permission("Dinar", 1));

  auto selected_ride =
      driver1->choose_order(drivers_gateway.get_available_rides());

  // check that there is a ride, which can be taken by driver
  if (selected_ride != nullptr) {
    try {
      drivers_gateway.take_ride(selected_ride, driver1);
    } catch (NoPermissionTakeRide e) {
      cout << "Driver cannot take a ride due to limitations" << endl;
    }
  }

  // update permission for a driver
  admin_gateway.update_permission(admin1->set_permission("Dinar", 0));
  drivers_gateway.take_ride(selected_ride, driver1);
  cout << "After updated permissions everything is okay" << endl;

  cout << "An attempt to create a new ride for a passenger who now is riding "
          "already"
       << endl;
  auto new_order = passenger1->create_order(
      Address("retake1"), Address("retake2"), car::CarType::Business, 0);
  if (get<0>(new_order) == nullptr) {
    cout << "User is already in the ride, and cannot create a new order"
         << endl;
  }

  drivers_gateway.complete_ride(selected_ride);
  new_order = passenger1->create_order(Address("retake1"), Address("retake2"),
                                       car::CarType::Business, 0);
  if (get<0>(new_order) != nullptr) {
    cout << "After finishing the ride everything is okay" << endl;
  }

  // code 1 for passenger means he cannot add a ride
  admin_gateway.update_permission(admin1->set_permission("Alex", 1));
  try {
    passenger_gateway.add_ride(new Ride(new_order));
  } catch (NoPermissionAddRide e) {
    cout << "User cannot add a ride, he is blocked" << endl;
  }

  admin_gateway.update_permission(admin1->set_permission("Alex", 0));
  cout << "After removing a ban, he can do it" << endl;
  passenger_gateway.add_ride(new Ride(new_order));

  // adding another order not to run out of orders for tests
  passenger_gateway.add_ride(new Ride(new_order));

  selected_ride = driver1->choose_order(drivers_gateway.get_available_rides());
  drivers_gateway.take_ride(selected_ride, driver1);

  cout << "Another ride was taken" << endl;
  // code 2 for passenger means he cannot ask for special parking
  admin_gateway.update_permission(admin1->set_permission("Alex", 2));

  try {
    passenger_gateway.ask_for_special_parking(selected_ride);
  } catch (NoPermissionAskForSpecialParking e) {
    cout << "User was blocked to ask for a special parking" << endl;
  }

  cout << "Current user location is "
       << passenger_gateway.get_current_coordinates(selected_ride) << endl;

  database::load_drivers(drivers);
  database::load_passengers(passengers);
  database::load_rides_completed(main_system->rides_completed);
  database::load_rides_pending(main_system->rides_pending);
  database::load_permissions(main_system->permissions);
  database::load_admins(main_system->admins);
}