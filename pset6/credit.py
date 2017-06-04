import cs50

        
def main():
    credit_card = str(get_input())
    
    even_numbers = get_even_numbers(credit_card)
    odd_numbers = get_odd_numbers(credit_card)
    sum_all_numbers = even_numbers + odd_numbers
    
    is_valid(credit_card, sum_all_numbers)
    
def get_input():
    while True:
        print("Card number: ", end="")
        cc = cs50.get_int()
        if cc > 0:
            break
    return cc
    
        
def get_even_numbers(credit_card):
    cc_copy = credit_card
    even_numbers_added = 0
    for x in range(len(credit_card)):
        cc_copy = int(cc_copy) // 10
        
        next_to_last_number = int(cc_copy) % 10
        cc_copy = int(cc_copy) // 10
        #double every other from second to last number
        doubled_numbers = int(next_to_last_number) * 2
        #if every other number is > 9 then subtract 9 to keep single digits
        if doubled_numbers > 9:
            doubled_numbers -= 9
        even_numbers_added += doubled_numbers
        
    return even_numbers_added


def get_odd_numbers(credit_card):
    everyother = 0
    cc_copy = credit_card
    
    for x in range(len(credit_card)):
        last_number = int(cc_copy) % 10
        cc_copy = int(cc_copy) / 100
        everyother += last_number
   
    return everyother
    
    
    
def is_valid(credit_card, sum_all_numbers):
    first_two_digits = 0
    first_two_digits = int(int(credit_card) / pow(10, len(credit_card)-2))
    
    if sum_all_numbers % 10 == 0:
        if first_two_digits == 34 or first_two_digits == 37:
            print("Valid AMEX card!")
        elif first_two_digits >= 40 and first_two_digits <= 49:
            print("Valid VISA card!")
        elif first_two_digits >= 51 and first_two_digits <= 55:
            print("Valid MASTERCARD!")
    
    else:
        print("Invalid card!")


main()
