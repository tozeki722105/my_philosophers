import subprocess
import sys

# filename = 'test.txt'
#  case1 no dead 
# ./philo 1 800 200 200
if sys.argv[1] == "1":
    result = subprocess.run(["../philo", "1", "800", "200", "200"])
    print(result)
    # with open(filename , 'w') as f:
    #     print(result,file = f)

#  case2 no dead 
# ./philo 5 800 200 200
elif sys.argv[1] == "2":
    result = subprocess.run(["../philo", "5", "800", "200", "200"])
    print(result)

#  case3 no dead 
# ./philo 5 800 200 200 7
elif sys.argv[1] == "3":
    result = subprocess.run(["../philo", "5", "800", "200", "200", "7"])
    print(result)

#  case4 may be dead 
# ./philo 4 410 200 200
elif sys.argv[1] == "4":
    result = subprocess.run(["../philo", "4", "410", "200", "200"])
    print(result)

#  case5 may be dead 
# ./philo 4 310 200 100
elif sys.argv[1] == "5":
    result = subprocess.run(["../philo", "4", "310", "200", "100"])
    print(result)

#  case6 error case
# ./philo 4 310 200 100 0
elif sys.argv[1] == "6":
    result = subprocess.run(["../philo", "4", "310", "200", "100", "0"])
    print(result)

#  case7 error case
# ./philo 0 310 200 100 1
elif sys.argv[1] == "7":
    result = subprocess.run(["../philo", "0", "310", "200", "100", "1"])
    print(result)

#  case8 error case
# ./philo 0 310 200 100 0
elif sys.argv[1] == "8":
    result = subprocess.run(["../philo", "0", "310", "200", "100", "0"])
    print(result)

#  case9 error case
# ./philo "" 310 200 100 0
elif sys.argv[1] == "9":
    result = subprocess.run(["../philo", "", "310", "200", "100", "0"])
    print(result)

#  case10 error case
# ./philo 2 "" 200 100 0
elif sys.argv[1] == "10":
    result = subprocess.run(["../philo", "2", "", "200", "100", "0"])
    print(result)

#  case11 error case
# ./philo 2 800 "" 100 0
elif sys.argv[1] == "11":
    result = subprocess.run(["../philo", "2", "800", "", "100", "0"])
    print(result)

#  case12 error case
# ./philo 2 800 200 ""
elif sys.argv[1] == "12":
    result = subprocess.run(["../philo", "2", "800", "200", ""])
    print(result)

#  case12 error case
# ./philo 2 800 200 ""
elif sys.argv[1] == "13":
    result = subprocess.run(["../philo", "4", "410", "300", "200"])
    print(result)

#  case12 error case INT_MAX + 1
# ./philo 2 800 200 ""
elif sys.argv[1] == "14":
    result = subprocess.run(["../philo", "4", "2147483648", "300", "200"])
    print(result)

#  case12 error case INT_MIN
# ./philo 2 800 200 ""
elif sys.argv[1] == "15":
    result = subprocess.run(["../philo", "4", "-2147483648", "300", "200"])
    print(result)
