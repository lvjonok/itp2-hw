#include <string>
#include "../database/parser.h"

#ifndef PAYMENT_METHODS_H
#define PAYMENT_METHODS_H

namespace payment {
enum class PaymentMethod { CARD, CASH };
std::string serialize_payment_method(PaymentMethod method) {
  switch (method) {
    case (PaymentMethod::CARD):
      return "Card";
    case (PaymentMethod::CASH):
      return "Cash";
  }
}

class Payment {
  PaymentMethod method;
  float money;

 public:
      Payment(PaymentMethod _method, float _money)
          : method(_method), money(_money) {}
      Payment(std::string serialized) {
        auto tokens = parser::parse_string(serialized, '/');
        if (tokens[0] == "Card") {
          method = PaymentMethod::CARD;
        }
        if (tokens[0] == "Cash") {
          method = PaymentMethod::CASH;
        }
        money = std::stof(tokens[1]);
      }
      // Method returns serialized payment method
      std::string serialize() {
        return serialize_payment_method(method) + "/" + std::to_string(money);
      }
      // Method returns amount of money on this payment method
      float get_money() { return money; }
      // We assume this Payment method has enough money to pay the bill
      void pay(float bill) { money -= bill; }
  };
}  // namespace payment

#endif