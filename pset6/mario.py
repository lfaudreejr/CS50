import cs50

def user_input():
    while True:
        print("Enter a Height: ", end="")
        height = cs50.get_int()
        if height > 0:
            break
    return height

def print_height():
    pyramid_height = user_input()
    space = " "
    count = 1
    space_count = pyramid_height - 1
    for x in range(pyramid_height):
        print(space * space_count + "#" * count + " " + "#" * count)
        count += 1
        space_count -= 1
    
def main():
    print_height()
    
    
main()