import pandas as pd
import matplotlib.pyplot as plt

multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
medianprops = dict(linestyle='-.', linewidth=2.5, color='black')


fig = plt.figure(layout='constrained', figsize=(10, 10))
axes = fig.subplots(3, 2)
fig.suptitle('Times for Different Decompositions')

for i, m in enumerate(multi):
    df1 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_1.txt", names=["time"])
    df2 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_2.txt", names=["time"])
    df3 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_3.txt", names=["time"])

    res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
    res = pd.merge(res, df3, left_index=True, right_index=True)
    res.rename(columns={"time_1":"config 1", "time_2":"config 2", "time":"config 3"}, inplace=True)
    ax = axes[i//2][i%2]
    ax.set_title(m)
    ax.set_ylabel('Execution time (s)')
    bplot, props = res.boxplot(
        ax=ax, 
        column=['config 1', 'config 2', 'config 3'],
        patch_artist=True,
        medianprops=medianprops,
        showmeans=False,
        showfliers=False,
        return_type='both',
        label=['config 1', 'config 2', 'config 3'],
    )
    colors = ['red', 'yellow', 'blue']

    for patch, color in zip(props['boxes'], colors):
        patch.set_facecolor(color)
    ax.legend()

plt.savefig("ghd_configurations")