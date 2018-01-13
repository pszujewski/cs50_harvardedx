import cs50
import modules

def getTotalChangeNeeded():
    print("O hai! How much change is owed?", end=" ")
    userInpt = cs50.get_float()
    toHundreth = userInpt * 100
    return int(toHundreth)

def handleEvalCoinToAdd(reg, coin):
    curr = reg.currChange
    total = reg.totalChangeNeeded
    shouldAddCoin = coin.evalCoinAgainstChange(curr, total)
    if shouldAddCoin:
        reg.incrementCurrentByCoinType(coin)
    return shouldAddCoin

def main():
    totalChangeNeeded = getTotalChangeNeeded()

    reg = modules.Register(totalChangeNeeded)

    coins = [
        modules.Coin(25, "quarter"),
        modules.Coin(10, "dime"),
        modules.Coin(5, "nickel"),
        modules.Coin(1, "penny")
    ]

    while reg.currChange < reg.totalChangeNeeded:

        coinIsRegistered = False

        for c in coins:
            if not coinIsRegistered:
                coinIsRegistered = handleEvalCoinToAdd(reg, c)

    print("Total coins needed: {}".format(str(reg.totalCoinsUsed)))

if __name__ == "__main__":
    main()


