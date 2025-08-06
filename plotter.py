import pandas as pd
import matplotlib.pyplot as plt

def min_time():
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    for i, m in enumerate(multi):
        df1 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_1.txt", names=["time"])
        df2 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_2.txt", names=["time"])
        df3 = pd.read_csv(f"runqueries/outputs/{m}_ghd_yk_3.txt", names=["time"])

        res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
        res = pd.merge(res, df3, left_index=True, right_index=True)
        res = res.min(axis=1)


def plot_config():
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

    plt.savefig("ghd_configurations")


patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "bowtie", "triangle_tadpole"]
medianprops = dict(linestyle='-.', linewidth=2.5, color='black')

fig = plt.figure(layout='constrained', figsize=(10, 10))
axes = fig.subplots(4, 2)
fig.suptitle('Times for Different Decompositions')
multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]

for i, p in enumerate(patterns):
    if p in multi:
        df1 = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_1.txt", names=["time"])
        df2 = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_2.txt", names=["time"])
        df3 = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_3.txt", names=["time"])

        yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
        yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
        yk_res["GHD"] = yk_res.min(axis=1)
        df1p = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_par_1.txt", names=["time"])
        df2p = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_par_2.txt", names=["time"])
        df3p = pd.read_csv(f"runqueries/outputs/{p}_ghd_yk_par_3.txt", names=["time"])

        ykp_res = pd.merge(df1p, df2p, left_index=True, right_index=True)
        ykp_res = pd.merge(ykp_res, df3p, left_index=True, right_index=True)
        ykp_res["GHD par"] = ykp_res.min(axis=1)
        df_mj = pd.read_csv(f"runqueries/outputs/{p}_ghd_mj.txt", names=["multijoin"])
    else:
        yk_res = pd.read_csv(f"runqueries/outputs/{p}_yk.txt", names=["GHD"])
        ykp_res = pd.read_csv(f"runqueries/outputs/{p}_yk_par.txt", names=["GHD par"])
        df_mj = pd.read_csv(f"runqueries/outputs/{p}_mj.txt", names=["multijoin"])

    res = pd.merge(yk_res[["GHD"]], ykp_res[["GHD par"]], left_index=True, right_index=True)
    res = pd.merge(res, df_mj, left_index=True, right_index=True)
    ax = axes[i//2][i%2]
    ax.set_title(p)
    ax.set_ylabel('Execution time (s)')
    bplot, props = res.boxplot(
        ax=ax,
        patch_artist=True,
        medianprops=medianprops,
        showmeans=False,
        showfliers=False,
        return_type='both',
    )
    colors = ['red', 'yellow', 'blue']

    for patch, color in zip(props['boxes'], colors):
        patch.set_facecolor(color)
handles, labels = plt.gca().get_legend_handles_labels()
fig.legend(handles, labels, loc='upper center')
plt.savefig("times")
