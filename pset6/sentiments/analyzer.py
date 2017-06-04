import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = set()
        self.negatives = set()
        
        with open(positives, 'r') as positive:
            for line in positive:
                if(line.startswith(';')):
                    continue
                else:
                    self.positives.add(line.rstrip('\n'))
            positive.close()
                    
        with open(negatives, 'r') as negative:
            for line in negative:
                if(line.startswith(';')):
                    continue
                else:
                    self.negatives.add(line.rstrip('\n'))
            negative.close()

        # TODO

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        total_score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        for token in tokens:
            lcase_token = token.lower()
            if lcase_token in self.positives:
                total_score += 1
            elif lcase_token in self.negatives:
                total_score -= 1
                

        return total_score
