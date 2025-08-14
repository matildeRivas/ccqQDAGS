import pandas as pd
import matplotlib.pyplot as plt

def min_time():
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    for i, m in enumerate(multi):
        df1 = pd.read_csv(f"outputs_time/{m}_ghd_yk_1.csv", names=["time"])
        df2 = pd.read_csv(f"outputs_time/{m}_ghd_yk_2.csv", names=["time"])
        df3 = pd.read_csv(f"outputs_time/{m}_ghd_yk_3.csv", names=["time"])

        res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
        res = pd.merge(res, df3, left_index=True, right_index=True)
        res = res.min(axis=1)


def plot_config():
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    medianprops = dict(linestyle='-.', linewidth=2.5, color='black')

    fig = plt.figure(layout='constrained', figsize=(10, 10))
    axes = fig.subplots(3, 2)
    fig.suptitle('Times for Different Decompositions in high arity qdag')

    for i, m in enumerate(multi):
        df1 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_1.csv", names=["time"])
        df2 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_2.csv", names=["time"])
        df3 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_3.csv", names=["time"])

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
        colors = ['firebrick', 'gold', 'cornflowerblue']

        for patch, color in zip(props['boxes'], colors):
            patch.set_facecolor(color)

    plt.savefig("outputs/ghd_configurations")

def plot_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
    medianprops = dict(linestyle='-.', linewidth=2.5, color='black')

    fig = plt.figure(layout='constrained', figsize=(10, 10))
    axes = fig.subplots(6, 2)
    fig.suptitle('Times for High Arity Qdag Variant')
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]

    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD"] = yk_res.min(axis=1)
            df1p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_1.csv", names=["time"])
            df2p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_2.csv", names=["time"])
            df3p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_3.csv", names=["time"])

            ykp_res = pd.merge(df1p, df2p, left_index=True, right_index=True)
            ykp_res = pd.merge(ykp_res, df3p, left_index=True, right_index=True)
            ykp_res["GHD par"] = ykp_res.min(axis=1)
            df_mj = pd.read_csv(f"outputs_time/ha_{p}_ghd_mj.csv", names=["multijoin"])
        else:
            yk_res = pd.read_csv(f"outputs_time/ha_{p}_yk.csv", names=["GHD"])
            ykp_res = pd.read_csv(f"outputs_time/ha_{p}_yk_par.csv", names=["GHD par"])
            df_mj = pd.read_csv(f"outputs_time/ha_{p}_mj.csv", names=["multijoin"])

        df_mj[df_mj['multijoin'] == 'timeout'] = 1800
        df_mj["multijoin"] = pd.to_numeric(df_mj["multijoin"], downcast='float')

        res = pd.merge(yk_res[["GHD"]], ykp_res[["GHD par"]], left_index=True, right_index=True)
        res = pd.merge(res, df_mj, left_index=True, right_index=True)
        ax = axes[i//2][i%2]
        ax.set_title(p)
        ax.set_ylabel('Execution time (s)')
        bplot, props = res.boxplot(
            ax=ax,
            column=["GHD", "GHD par", "multijoin"],
            patch_artist=True,
            medianprops=medianprops,
            showmeans=False,
            showfliers=False,
            return_type='both',
        )
        colors = ['firebrick', 'gold', 'cornflowerblue']

        for patch, color in zip(props['boxes'], colors):
            patch.set_facecolor(color)

    handles, labels = plt.gca().get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper center')
    plt.savefig("outputs/times")

def yk_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
   
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"Pattern": [], "Mean difference": [], "Median difference": [], "Max difference": []}
    df = pd.DataFrame(data)
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD"] = yk_res.min(axis=1)
            df1p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_1.csv", names=["time"])
            df2p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_2.csv", names=["time"])
            df3p = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_par_3.csv", names=["time"])

            ykp_res = pd.merge(df1p, df2p, left_index=True, right_index=True)
            ykp_res = pd.merge(ykp_res, df3p, left_index=True, right_index=True)
            ykp_res["GHD par"] = ykp_res.min(axis=1)
        else:
            yk_res = pd.read_csv(f"outputs_time/ha_{p}_yk.csv", names=["GHD"])
            ykp_res = pd.read_csv(f"outputs_time/ha_{p}_yk_par.csv", names=["GHD par"])

        res = pd.merge(yk_res[["GHD"]], ykp_res[["GHD par"]], left_index=True, right_index=True)
        res["diff"] = 100*(1 - res["GHD par"] / res["GHD"])
        row = {"Pattern": p, "Mean difference": round(res["diff"].mean(),2), "Median difference": round(res["diff"].median(),2), "Max difference":round(res["diff"].max(),2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/ha_percentages.csv", index=False)
        
