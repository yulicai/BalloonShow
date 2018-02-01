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
tags = blob.tags
for word,tag in blob.tags:
    if ("JJ" in tag):
        word_list.append(word)
    elif("JJR" in tag):
        word_list.append(word)
    elif("JJS" in tag):
        word_list.append(word)
        # print word
#take out words:
#i, like
take_out_words = ['i', 'like','yeah', 'other']
for word in word_list:
    if (word in take_out_words):
        word_list.remove(word)


counter = Counter(word_list)
print counter
most_common = counter.most_common(20)
for item in most_common:
    print item[0]

# for item in most_common:
    # print item[0]
