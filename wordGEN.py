from english_words import get_english_words_set
web2lowerset = get_english_words_set(['web2'], lower=True)


f = open("words.txt", "a")
for i in web2lowerset:
	f.write(f"{i}\n")
f.close()