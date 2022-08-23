#include "server.h"
#include <string.h>
uint32_t transactionSequenceNumberStatic=0;
EN_serverError_t init_valid_accounts_database(void)
{
    valid_accounts_database[0].balance=100.5;
    strcpy(valid_accounts_database[0].primaryAccountNumber,"1234567890123456");
    valid_accounts_database[0].state=BLOCKED;
    //RUNNING;
    return OK_server;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData,ST_accountsDB_t *accountRefrence)
{
    //This function will take card data and validate these data.
    //It checks if the PAN exists or not in the server's database.
    //If the PAN doesn't exist will return ACCOUNT_NOT_FOUND, else will return OK
    uint8_t i;
    for(i=0;i<20;i++)
    {
        if((cardData->primaryAccountNumber[i]==0)||(accountRefrence->primaryAccountNumber[i]==0))
            break;
        if((cardData->primaryAccountNumber[i])!=(accountRefrence->primaryAccountNumber[i]))
        {
            return ACCOUNT_NOT_FOUND;
        }
    }
    return OK_server;
}
/*
This function will take a reference to an existing account in the database.
It checks if the account is blocked or not.
If the account is blocked, will return BLOCKED_ACCOUNT, else will return SERVER_OK.
*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    //This function will take a reference to an existing account in the database.
    //It checks if the account is blocked or not.
    //If the account is blocked, will return BLOCKED_ACCOUNT, else will return SERVER_OK.
    if(accountRefrence->state==BLOCKED)
        return BLOCKED_ACCOUNT;
    return OK_server;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    //This function will take terminal data and validate these data.
    //It checks if the transaction's amount is available or not.
    //If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return OK
    if(termData->transAmount>=valid_accounts_database[0].balance)
        return LOW_BALANCE;
    return OK_server;
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    //This function will take a transaction sequence number and search for this transaction in the database.
    //If the transaction can't be found will return TRANSACTION_NOT_FOUND, else will return OK and store the transaction in a structure
    if((transaction_database[transactionSequenceNumber].transactionSequenceNumber)==(transData->transactionSequenceNumber))
        return OK_server;
    uint8_t i;
    for(i=0;i<255;i++)
    {
        if(transaction_database[i].transactionSequenceNumber==transData->transactionSequenceNumber)
            return OK_server;
    }
    return TRANSACTION_NOT_FOUND;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    //This function will take all transaction data into the transactions database.
    //It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
    transData->transactionSequenceNumber=transactionSequenceNumberStatic;
    //It saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
    if(transData->transState != APPROVED)
        return SAVING_FAILED;
    //If transaction can't be saved will return SAVING_FAILED, else will return OK
    if(transactionSequenceNumberStatic>255)
        return SAVING_FAILED;
    transaction_database[transactionSequenceNumberStatic]=*transData;
    //transaction_database[transactionSequenceNumberStatic].transactionSequenceNumber=transData->transactionSequenceNumber;
    transactionSequenceNumberStatic++;
    return OK_server;
}
