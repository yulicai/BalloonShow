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
for phrases in noun_phrases:
    print phrases


counter = Counter(noun_phrases)
# print counter
most_common = counter.most_common(20)
print "###### Most Common 20 ###### "
for item in most_common:
    print item[0]

# for item in most_common:
    # print item[0]
