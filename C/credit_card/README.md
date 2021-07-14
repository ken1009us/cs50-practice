# Validating credit card numbers
```
To validate and distinguish the credit card numbers which the user entered.
----------------------------------------------------------------------------
three types of credit card:
1. American Express start with: 34, 37
2. Mastercard start with: 51~55
3. Visa start with: 4
```

```
include <cs50.h>
include <stdio.h>
```

```
Preparation:
1. Go to https://github.com/cs50/libcs50/releases
2. Download the latest release of the library
3. Extract the contents to a folder
4. Navigate to the above folder - run sudo make install
```

```
Steps:
1. clang -o credit credit.c -lcs50
2. ./credit
```