### Zorba Query Plan
Save query plan when running a query multiple times to save time
- usage

		zorba -q 1+1 --compile-plan -o simple.xqc
		zorba -q simple.xqc -f --execute-plan
