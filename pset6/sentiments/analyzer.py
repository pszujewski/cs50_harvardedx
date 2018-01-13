import nltk
import helpers

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # initialize two dicts attached to the class
        # initialize dict for tracking total number of each 'type' of tweet for the plotly html chart
        self.positive_words = {}
        self.negative_words = {}
        self.classifications = {
            "positives": 0,
            "negatives": 0,
            "neutrals": 0
        }
        self.total_tweets = 0

        # Load the words into two dicts (positive and negative)
        self.loadWordSet(positives, self.positive_words, True)
        self.loadWordSet(negatives, self.negative_words, False)

    def loadWordSet(self, wordsFile, structure, isPositive):
        # dont include comments starting with a semi-colon
        # strip off whitespace and add the word as a key in the dicts
        # with the appropriate value
        file = open(wordsFile, "r")
        for word in file:
            if not word.startswith(";"):
                structure[word.strip()] = 1 if isPositive else -1
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # tokenize the input and return search result
        allLowerCase = text.lower()
        tokensList = nltk.word_tokenize(allLowerCase)

        return self.searchForWord(tokensList)

    def searchForWord(self, tokensList):
        # iterate over list of tokens
        # check if in each dict container
        # if not in either dicts, it is a neutral word
        for i in range(len(tokensList)):
            word = tokensList[i]
            if word in self.positive_words:
                return self.positive_words[word]
            elif word in self.negative_words:
                return self.negative_words[word]
        return 0

    def getTweetTokens(self, screen_name):
        # the total tweets is simply the number of tweets we get back from
        # the query. We get the score for each tweet and also classify it all at once
        # dict structure allows us to store all this data for one tweet.
        tweets = helpers.get_user_timeline(screen_name, 50)
        tokenizer = nltk.tokenize.TweetTokenizer()
        tweet_collection = []
        self.total_tweets = len(tweets)
        for i in range(len(tweets)):
            tweet = tweets[i]
            tweet_tokens = tokenizer.tokenize(tweet)
            score = self.getTweetScore(tweet_tokens)
            classification = self.getTweetClassification(score)
            tweet_entry = {
                "tweet_content": tweet,
                "score": score,
                "classification": classification
            }
            # each tweet dict is appended to the list
            tweet_collection.append(tweet_entry)
        return tweet_collection


    def getTweetScore(self, tweet_tokens):
        score = 0
        num_tokens = range(len(tweet_tokens))
        for i in num_tokens:
            token = tweet_tokens[i].lower()
            if token in self.positive_words:
                score = score + 1
            elif token in self.negative_words:
                score = score - 1
        return score


    def getTweetClassification(self, score):
        if score > 0:
            self.classifications["positives"] += 1
            return "positive"
        elif score < 0:
            self.classifications["negatives"] += 1
            return "negative"
        else:
            self.classifications["neutrals"] += 1
            return "neutral"


    # helper functions for printing dictionary results

    def printWords(self, setName):
        if setName == "positives":
            self.printOneSet(self.positive_words)
        else:
            self.printOneSet(self.negative_words)

    def printOneSet(self, setRef):
        for key in setRef:
            print(setRef[key])
