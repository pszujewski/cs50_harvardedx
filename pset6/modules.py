class Coin:
    def __init__(self, coinValue, coinName):
        self.value = coinValue
        self.name = coinName

    def evalCoinAgainstChange(self, currChange, totalChangeNeeded):
        return self.value + currChange <= totalChangeNeeded

class Register:
    def __init__(self, totalChangeNeeded):
        self.currChange = 0
        self.totalChangeNeeded = totalChangeNeeded
        self.totalCoinsUsed = 0

    def incrementCurrentByCoinType(self, coin):
        self.currChange += coin.value
        self.totalCoinsUsed += 1
        print("We need a {}".format(coin.name))


