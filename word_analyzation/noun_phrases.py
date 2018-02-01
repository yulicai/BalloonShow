import sys,string
from textblob import TextBlob
from collections import Counter
import codecs

whole_line = ""
word_list = []
text = sys.stdin.read()
text = text.lower()
text = text.translate(string.maketrans("",""), string.punctuation)
# text = sys.stdin.read().decode('ascii', errors="replace")
blob = TextBlob(text)

noun_phrases = blob.noun_phrases
# print noun_phrases
# take_out_words = ['i don\'t', 'i guess','gon na', 'i didnt']
# for phrase in noun_phrases:
#     if (phrase in take_out_words):
#         noun_phrases.remove(phrase)



counter = Counter(noun_phrases)
# print counter
all_words = counter.keys()

print "<<<<<<<<<<<<<< ALL THE NOUN_PHRASES"
for word in all_words:
    print word
print "<<<<<<<<<<<<<< FOLLOWING ARE TOP 40"
most_common = counter.most_common(40)
for item in most_common:
    print item[0]

# for item in most_common:
    # print item[0]
