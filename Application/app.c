#include"app.h"
#define test_index 0
void appStart(void)
{
    //start
    puts("start");
    //============================================================================
    //CARD
    ST_cardData_t cardData;
    //get holder name
    if(getCardHolderName(&cardData)!=OK_card)
        puts("error getCardHolderName");
    //get card expiration date
    if(getCardExpiryDate(&cardData)!=OK_card)
        puts("error getCardExpiryDate");
    //get card pan
    if(getCardPAN(&cardData)!=OK_card)
        puts("error getCardPAN");
    //============================================================================
    //terminal
    ST_terminalData_t termData;
    //get all card data

    //get transaction date
    if(getTransactionDate(&termData)!=OK_terminal)
        puts("error getTransactionDate");
    //IF is card expired
    if(isCardExpired(&cardData,&termData)==EXPIRED_CARD)
    {
        //1(IF is card expired) => decline expired card  => failed
        puts("decline expired card");
        puts("failed");
        return;
    }
    //get transaction amount
    if(getTransactionAmount(&termData)!=OK_terminal)
        puts("error getTransactionAmount");
    //IF is exceeded amount
    if(setMaxAmount(&termData)!=OK_terminal)
        puts("error setMaxAmount");
    if(isBelowMaxAmount(&termData)==EXCEED_MAX_AMOUNT)
    {
        //1(IF is exceeded amount) => decline exceeded amount  => failed
        puts("decline exceeded amount");
        puts("failed");
        return;
    }

    //============================================================================
    //SERVER
    ST_transaction_t transData;
    transData.cardHolderData=cardData;
    transData.terminalData=termData;
    transData.transState=APPROVED;
    transData.transactionSequenceNumber=0;
    if(init_valid_accounts_database()!=OK_server)
        puts("error init_valid_accounts_database");
    //IF is valid account
    if(isValidAccount(&cardData,&valid_accounts_database[test_index])==ACCOUNT_NOT_FOUND)
    {
        //0(IF is valid account) => decline invalid account  => failed
        puts("decline invalid account");
        puts("failed");
        return;
    }
    if(isBlockedAccount(&valid_accounts_database[test_index])==BLOCKED_ACCOUNT)
    {
        puts("decline BLOCKEDACCOUNT");
        puts("failed");
        return;
    }
    //IF is amount available
    if(isAmountAvailable(&termData)==LOW_BALANCE)
    {
        //0(IF is amount available) => decline insufficient funds => failed
        puts("decline insufficient funds");
        transData.transState=DECLINED_INSUFFECIENT_FUND;
        puts("failed");
        return;
    }
    //update account balance
    valid_accounts_database[test_index].balance-=termData.transAmount;
    //save transaction

    if(saveTransaction(&transData)!=OK_server)
        puts("error saveTransaction");
    //end passed
    puts("passed");
    //puts("end with 0 problems");
}
