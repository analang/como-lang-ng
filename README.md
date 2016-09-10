# COMO: como object meta oriented

# even.como
```
func isodd(num) {
	i = 0;
	odd = 0;
	while((i == num) == 0) {
		if(odd == 0) {
			odd = 1;
		} else {
			odd = 0;
		}
		i = i + 1;
	}
	return odd;
}

func print_even(num)
{
	while(num) {
		if(isodd(num)) {
			print(num + " is odd");
		} else {
			print(num + " is even");
		}
		num = num - 1;
	}
}

print_even(4);
```

# range
```
func print_range(a, b) {
	while(a <= b) {
		print(a);
		a = a + 1;
	}
}
```


# License
Please see the file LICENSE located in the root directory of the project.
