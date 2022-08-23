#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t i;
    for(i=0;i<11;i++)
    {
        termData->transactionDate[i]=0;
    }
    //ask for the transaction data
    puts("transaction date ????????????????");
    puts("DD/MM/YYYY");
    //uint8_t transactionDate[11]; => store it in terminal data
    //uint8_t transactionDate[11]; => 10 characters string => format DD/MM/YYYY, e.g 25/06/2022
    scanf("%s",termData->transactionDate);
    for(i=0;i<10;i++)
    {
        if((i==2)||(i==5))
            continue;
        if((termData->transactionDate[i]>'9')||(termData->transactionDate[i]<'0'))
            return WRONG_DATE;
    }
    //If (the transaction date == NULL || less than 10 characters )
    if ((!(termData->transactionDate[0]))||((termData->transactionDate[10])))
    {
        return WRONG_DATE;
    }
    // || if (wrong format) return WRONG_DATE;
    // DD/MM/YYYY  ok
    // YYYY/mm/dd
    // DD/YYYY/MM
    if (((termData->transactionDate[2])!='/')||((termData->transactionDate[5])!='/')||((termData->transactionDate[3])>'1'))
    {
        return WRONG_DATE;
    }
    //else return OK;
    return OK_terminal;
}
/*
This function compares the card expiry date with the transaction date.
If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK.
You should deliver a maximum 2min video to discuss your implementation and run different test cases on this function
*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    //compares the card expiry date with the transaction date
    //If the card expiration date is before the transaction date will return EXPIRED_CARD
    //If (card expiration date < the transaction date) return EXPIRED_CARD;
    //if((cardData->cardExpirationDate[3])>(termData->transactionDate[8]))
    if((((cardData->cardExpirationDate[3])*10)+(cardData->cardExpirationDate[4]))>(((termData->transactionDate[8])*10)+(termData->transactionDate[9])))
        return OK_terminal;
    if((((cardData->cardExpirationDate[3])*10)+(cardData->cardExpirationDate[4]))==(((termData->transactionDate[8])*10)+(termData->transactionDate[9])))
    {
        if((((cardData->cardExpirationDate[0])*10)+(cardData->cardExpirationDate[1]))>=(((termData->transactionDate[3])*10)+(termData->transactionDate[4])))
            return OK_terminal;
    }
    return EXPIRED_CARD;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float x;
    //This function asks for the transaction amount
    puts("transaction amount ????????????????");
    //float transAmount => saves it into terminal data
    scanf("%f",&x);
    //If(transaction amount  <= 0)  return INVALID_AMOUNT; return OK;
    if(x<=0)
        return INVALID_AMOUNT;
    termData->transAmount=x;
    return OK_terminal;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    //This function compares the transaction amount with the terminal max amount.
    //if(transaction amount > terminal max amount) return EXCEED_MAX_AMOUNT; return OK;
    if(termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    return OK_terminal;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    //This function sets the maximum allowed amount into terminal data.
    //Transaction max amount is a float number.
    termData->maxTransAmount=100000000.0;
    //If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.
    if(termData->maxTransAmount<=0)
        return INVALID_AMOUNT;
    return OK_terminal;
}
