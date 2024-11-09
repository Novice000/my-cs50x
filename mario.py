from cs50 import get_int

def main():
    while True:
        height= get_int('Height: ')
        if height >= 1 and height <=8:
            break

    for i in range(height):
       statement= f"{space(height-(i+1))}{'#'*(i+1)}  {'#'*(i+1)}"
       print(statement)












def space(n):
    return ' '*n




main()



