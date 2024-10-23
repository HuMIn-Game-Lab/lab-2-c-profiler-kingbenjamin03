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




data.columns = data.columns.str.strip()

# Extracting relevant columns
sections = data['Section']
total_time = data['Total Time']
std_devs = data['Standard Deviation']

# Create a Pandas DataFrame with the relevant data
df = pd.DataFrame({
    'Section': sections,
    'Total Time': total_time,
    'Standard Deviation': std_devs
})

# Create a stacked bar plot for Total Time and Standard Deviation
plt.figure(figsize=(10, 6))

# Plotting total time as the base
plt.bar(df['Section'], df['Total Time'], label='Total Time', color='lightblue')

# Overlaying standard deviation on top of total time
plt.bar(df['Section'], df['Standard Deviation'], bottom=df['Total Time'], label='Standard Deviation', color='orange')

# Adding titles and labels
plt.title("Total Time with Standard Deviation on Top")
plt.xlabel("Section")
plt.ylabel("Time (seconds)")

# Rotate x-axis labels for better readability
plt.xticks(rotation=45, ha='right')

# Adding a legend
plt.legend()

# Show the plot
plt.tight_layout()
plt.show()