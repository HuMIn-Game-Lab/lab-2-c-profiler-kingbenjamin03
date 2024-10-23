import pandas as pd
import matplotlib.pyplot as plt
#input = pd.read_csv('Code/ProfilerStats.csv')  # Read the CSV file into a DataFrame


file_path = 'Data/ProfilerStats.csv'
#file_path = '/Users/benking/Documents/GitHub/lab-2-c-profiler-kingbenjamin03/Data/ProfilerStats.csv'  
data = pd.read_csv(file_path)
#print(data.columns)  # Display the column names of the DataFrame


data.plot(x='Section', y=' Avg Time', kind='bar', color='orange')
plt.title('Avg Time per Section')
plt.xlabel('Section')
plt.ylabel('Avg Time (Sec)')
plt.xticks(rotation=45)
plt.show()






# data.plot(x='Section', y=' Avg Time', kind='bar', color='blue')

# plt.title('Avg Time per Section (Sec)')
# plt.xlabel('Section')
# plt.ylabel('Avg Time')
# plt.xticks(rotation=45)
# plt.show()



#print(data.columns)  # Display the column names of the DataFrame
# plt.plot(data['Section'], data[' Total Time'], marker='o', linestyle='-', color='b')

# plt.title('Total Time per Section')
# plt.xlabel('Section')
# plt.ylabel('Total Time')
# plt.xticks(rotation=45)
# plt.grid(True)
# plt.show()