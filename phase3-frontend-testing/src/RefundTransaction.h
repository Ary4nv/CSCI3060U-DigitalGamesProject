#ifndef REFUNDTRANSACTION_H
#define REFUNDTRANSACTION_H

#include "Transaction.h"

// The refund transaction (admin only). Moves credit from a seller back to a buyer.
class RefundTransaction : public Transaction {
public:
    // Makes a refund transaction.
    RefundTransaction(Console& console, Session& session);
    // Asks for the buyer, seller and amount, checks the seller has enough credit
    // and the buyer won't go over the maximum, moves the credit and records a refund (05) line.
    virtual void execute();
    // Only admins can refund.
    virtual bool isPermittedFor(const Account& user) const;
};

#endif
