#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8_t i;
    for(i=0;i<25;i++)
    {
        cardData->cardHolderName[i]=0;
    }
    //ask for the cardholder's name
    puts("cardholder's name ????????????????");
    //ST_cardData_t *cardData => store it into card data
    //uint8_t cardHolderName[25] => Card holder name is 24 characters string max and 20 min.
    scanf("%s",cardData->cardHolderName);
    //if(NULL, less than 20 characters or more than 24) return WRONG_NAME;
    if ((!(cardData->cardHolderName[0]))||(!(cardData->cardHolderName[19]))||(cardData->cardHolderName[24]))
    {
        return WRONG_NAME;
    }
    //else return OK;
    return OK_card;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t i;
    for(i=0;i<6;i++)
    {
        cardData->cardExpirationDate[i]=0;
    }
    //ask for the card expiry date
    puts("card expiry date ????????????????");
    puts("MM/YY");
    //uint8_t cardExpirationDate[6]; = >store it in card data => 5 characters string in the format "MM/YY", e.g "05/25"
    scanf("%s",cardData->cardExpirationDate);
    for(i=0;i<5;i++)
    {
        if(i==2)
            continue;
        if((cardData->cardExpirationDate[i]>'9')||(cardData->cardExpirationDate[i]<'0'))
            return WRONG_EXP_DATE;
    }
    //If(card expiry date ==NULL || less or more than 5 characters) || if(wrong format)  return WRONG_EXP_DATE;
    if ((!(cardData->cardExpirationDate[0]))||(!(cardData->cardExpirationDate[4]))||(cardData->cardExpirationDate[5]))
    {
        return WRONG_EXP_DATE;
    }
    if (((cardData->cardExpirationDate[2])!='/')||((cardData->cardExpirationDate[0])>'1'))
    {
        return WRONG_EXP_DATE;
    }
    if(((((cardData->cardExpirationDate[0])-'0')*10)+((cardData->cardExpirationDate[1])-'0'))>12)
    {
        return WRONG_EXP_DATE;
    }
    //else return OK;
    return OK_card;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8_t i;
    for(i=0;i<20;i++)
    {
        cardData->primaryAccountNumber[i]=0;
    }
    //ask for the card's Primary Account Number
    puts("Primary Account Number ????????????????");
    //uint8_t primaryAccountNumber[20]; => store it in card data => max 19 min 16
    scanf("%s",cardData->primaryAccountNumber);
    for(i=0;i<19;i++)
    {
        //printf("%d\n",cardData->primaryAccountNumber[i]-'0');
        if(cardData->primaryAccountNumber[i]==0)
            break;
        if((cardData->primaryAccountNumber[i]>'9')||(cardData->primaryAccountNumber[i]<'0'))
            return WRONG_PAN;
    }
    //If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error
    if ((!(cardData->primaryAccountNumber[0]))||(!(cardData->primaryAccountNumber[15]))||(cardData->primaryAccountNumber[19]))
    {
        return WRONG_PAN;
    }
    //else return OK;
    return OK_card;
}
