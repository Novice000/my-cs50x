from cs50 import get_int

def main():
    card= get_int('Number: ')
    card_str= str(card)
    card_len= len(card_str)
    if card_len not in [13,15,16]:
        print('INVALID')
        return

    string=''
    sum_1=0
    sum_2=0
    card_mod= card_len%2
    for i in range(card_len):
        if i%2 == card_mod:
            string = string + str(int(card_str[i])*2)
        else:
            sum_1 = sum_1 + int(card_str[i])

    for j in range(len(string)):
        sum_2 = sum_2 + int(string[j])
        
    total= sum_1+sum_2

    total_str= str(total)
    if total_str[len(total_str)-1] != '0':
        print('INVALID')
        return
    if card_str[0] == '4':
        print('VISA')
    elif card_str[:2] in ['34','37']:
        print('AMEX')
    elif int(card_str[:2]) >= 51 and int(card_str[:2]) <= 55:
        print('MASTERCARD')
    else:
        print('INVALID')


main()
