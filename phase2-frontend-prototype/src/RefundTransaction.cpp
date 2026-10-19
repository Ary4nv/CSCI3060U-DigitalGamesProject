#include "RefundTransaction.h"
#include "Messages.h"

// Makes a refund transaction.
RefundTransaction::RefundTransaction(Console& newConsole, Session& newSession)
    : Transaction(newConsole, newSession) {
}

// Only admins can refund.
bool RefundTransaction::isPermittedFor(const Account& user) const {
    return user.isAdmin();
}

// Asks for the buyer, seller and amount, checks the seller has enough credit
// and the buyer won't go over the maximum, moves the credit and records a refund (05) line.
void RefundTransaction::execute() {
    Account* buyer = askForExistingAccount(Messages::BUYER_USERNAME_PROMPT);
    if (buyer == NULL) {
        return;
    }
    Account* seller = askForExistingAccount(Messages::SELLER_USERNAME_PROMPT);
    if (seller == NULL) {
        return;
    }
    if (buyer->getUsername() == seller->getUsername()) {
        console.showError(Messages::BUYER_AND_SELLER_MUST_DIFFER);
        return;
    }

    Cents amount = 0;
    if (!askForPositiveAmount(amount)) {
        return;
    }
    if (seller->getCredit() < amount) {
        console.showError(Messages::NOT_ENOUGH_CREDIT);
        return;
    }
    if (!buyer->canReceive(amount)) {
        console.showError(Messages::CREDIT_LIMIT_EXCEEDED);
        return;
    }

    // refund money always comes out of the seller
    seller->removeCredit(amount);
    buyer->addCredit(amount);
    session.getLog().recordRefund(buyer->getUsername(), seller->getUsername(), amount);
    console.show(Messages::REFUND_COMPLETE);
}
