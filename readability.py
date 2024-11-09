from cs50 import get_string

def main():
    text = get_string('Text: ')

    letter_count= 0
    word_count= 1
    sen_count=0
    text_len= len(text)

    for i in range(text_len):
        if text[i].isalpha():
            letter_count += 1
        if text[i] == ' ':
            word_count += 1
        if text[i] in ['.', '?', '!']:
            sen_count += 1

    lpw= (letter_count/word_count) * 100
    spw= (sen_count/word_count) * 100

    coleman= round(0.0588 * lpw - 0.296 * spw - 15.8)

    if coleman < 1:
        print('Before Grade 1')
    elif coleman > 16:
        print('Grade 16+')
    else:
        print(f"Grade {coleman}")
main()
