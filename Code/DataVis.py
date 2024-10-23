import pandas as pd
import matplotlib.pyplot as plt
#input = pd.read_csv('Code/ProfilerStats.csv')  # Read the CSV file into a DataFrame


file_path = 'Data/ProfilerStats.csv'
#file_path = '/Users/benking/Documents/GitHub/lab-2-c-profiler-kingbenjamin03/Data/ProfilerStats.csv'  
data = pd.read_csv(file_path)
#print(data.columns)  # Display the column names of the DataFrame




ax = data.plot(x='Section', y=' Avg Time', kind='bar', color='orange')

# Add title and labels
plt.title('Avg Time per Section Over 1000 Runs')
plt.xlabel('Section')
plt.ylabel('Avg Time (Sec)')
plt.xticks(rotation=0)

# Add values on top of each bar
for container in ax.containers:
    ax.bar_label(container, label_type='edge', fmt='%.4f')

# Show the plot
plt.tight_layout()
plt.show()


ax = data.plot(x='Section', y=' Total Time', kind='bar', color='blue')

# Add title and labels
plt.title('Total Time per Section Over 1000 Runs')
plt.xlabel('Section')
plt.ylabel('Total Time (Sec)')
plt.xticks(rotation=0)

# Add values on top of each bar
for container in ax.containers:
    ax.bar_label(container, label_type='edge', fmt='%.4f')

# Show the plot
plt.tight_layout()
plt.show()

