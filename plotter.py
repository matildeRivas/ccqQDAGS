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
    multi = ["J3", "T3", "Ti3"] # , "T4", "Ti4", "J4",
    medianprops = dict(linestyle='-.', linewidth=2.5, color='black')

    fig = plt.figure(layout='constrained', figsize=(15,5))
    axes = fig.subplots(1, 3)
    fig.suptitle('Query Times for Decompositions')

    for i, m in enumerate(multi):
        df1 = pd.read_csv(f"outputs_time/config_{m}_ghd_yk_1.csv", names=["time"])
        df2 = pd.read_csv(f"outputs_time/config_{m}_ghd_yk_2.csv", names=["time"])
        df3 = pd.read_csv(f"outputs_time/config_{m}_ghd_yk_3.csv", names=["time"])

        res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
        res = pd.merge(res, df3, left_index=True, right_index=True)
        res.rename(columns={"time_1":"smallest", "time_2":"medium", "time":"largest"}, inplace=True)
        ax = axes[i%3]
        ax.set_title(m)
        ax.set_ylabel('Execution time (s)')
        #ax.set_xlabel('Which relation was left out of initial multijoin')
        bplot, props = res.boxplot(
            ax=ax, 
            column=['smallest', 'medium', 'largest'],
            patch_artist=True,
            medianprops=medianprops,
            showmeans=False,
            showfliers=False,
            return_type='both',
        )
        colors = ['firebrick', 'gold', 'cornflowerblue']

        for patch, color in zip(props['boxes'], colors):
            patch.set_facecolor(color)

    plt.savefig("outputs/triangle_ghd_configurations")

def plot_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "bowtie", "triangle_tadpole"]
    medianprops = dict(linestyle='-.', linewidth=2.5, color='black')

    fig = plt.figure(layout='constrained', figsize=(10, 10))
    axes = fig.subplots(4, 2)
    fig.suptitle('Times for Original Qdag Variant')
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]

    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD"] = yk_res.min(axis=1)

            df1p = pd.read_csv(f"outputs_time/{p}_ghd_yk_par_1.csv", names=["time"])
            df2p = pd.read_csv(f"outputs_time/{p}_ghd_yk_par_2.csv", names=["time"])
            df3p = pd.read_csv(f"outputs_time/{p}_ghd_yk_par_3.csv", names=["time"])

            ykp_res = pd.merge(df1p, df2p, left_index=True, right_index=True)
            ykp_res = pd.merge(ykp_res, df3p, left_index=True, right_index=True)
            ykp_res["GHD par"] = ykp_res.min(axis=1)

            df_np1 = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_1.csv", names=["time"])
            df_np2 = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_2.csv", names=["time"])
            df_np3 = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_3.csv", names=["time"])

            yk_np_res = pd.merge(df_np1, df_np2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_np_res = pd.merge(yk_np_res, df_np3, left_index=True, right_index=True)
            yk_np_res["GHD without pruning"] = yk_np_res.min(axis=1)

            df_mj = pd.read_csv(f"outputs_time/{p}_ghd_mj.csv", names=["multijoin"])
        else:
            yk_res = pd.read_csv(f"outputs_time/{p}_yk.csv", names=["GHD"])
            ykp_res = pd.read_csv(f"outputs_time/{p}_yk_par.csv", names=["GHD par"])
            df_mj = pd.read_csv(f"outputs_time/{p}_mj.csv", names=["multijoin"])
            yk_np_res = pd.read_csv(f"outputs_time/no_pruning_{p}_yk.csv", names=["GHD without pruning"])

        df_mj[df_mj['multijoin'] == 'timeout'] = 1800
        df_mj["multijoin"] = pd.to_numeric(df_mj["multijoin"], downcast='float')

        res = pd.merge(yk_res[["GHD"]], ykp_res[["GHD par"]], left_index=True, right_index=True)
        res = pd.merge(res, yk_np_res, left_index=True, right_index=True)
        res = pd.merge(res, df_mj, left_index=True, right_index=True)
        ax = axes[i//2][i%2]
        ax.set_title(p)
        ax.set_ylabel('Execution time (s)')
        bplot, props = res.boxplot(
            ax=ax,
            column=["GHD", "GHD par", "GHD without pruning"],#, "multijoin"],
            patch_artist=True,
            medianprops=medianprops,
            showmeans=False,
            showfliers=False,
            return_type='both',
        )
        colors = ['firebrick', 'gold', 'cornflowerblue', 'mediumorchid']

        for patch, color in zip(props['boxes'], colors):
            patch.set_facecolor(color)

    handles, labels = plt.gca().get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper center')
    plt.savefig("times")


def compare_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "bowtie"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"Pattern": [], "Mean factor mj": [], "Mean factor ghd": []}
    df = pd.DataFrame(data)
    
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD_og"] = yk_res.min(axis=1)
            df_mj = pd.read_csv(f"outputs_time/{p}_ghd_mj.csv", names=["multijoin_og"])


            df1ha = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_ghd_yk_1.csv", names=["time"])
            df2ha = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_ghd_yk_2.csv", names=["time"])
            df3ha = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_ghd_yk_3.csv", names=["time"])
            df_mj_ha = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_ghd_mj.csv", names=["multijoin_ha"])
            ykp_res = pd.merge(df1ha, df2ha, left_index=True, right_index=True)
            ykp_res = pd.merge(ykp_res, df3ha, left_index=True, right_index=True)
            ykp_res["GHD_ha"] = ykp_res.min(axis=1)
        else:
            yk_res = pd.read_csv(f"outputs_time/{p}_yk.csv", names=["GHD_og"])
            ykp_res = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_yk.csv", names=["GHD_ha"])
            df_mj = pd.read_csv(f"outputs_time/{p}_mj.csv", names=["multijoin_og"])
            df_mj_ha = pd.read_csv(f"/mnt/c/Users/crist/Documents/mati/ha_outputs_time/ha_{p}_mj.csv", names=["multijoin_ha"])

        df_mj[df_mj['multijoin_og'] == 'timeout'] = 1800
        df_mj["multijoin_og"] = pd.to_numeric(df_mj["multijoin_og"], downcast='float')
        
        df_mj_ha[df_mj_ha['multijoin_ha'] == 'timeout'] = 1800
        df_mj_ha["multijoin_ha"] = pd.to_numeric(df_mj_ha["multijoin_ha"], downcast='float')
        res = pd.merge(yk_res[["GHD_og"]], ykp_res[["GHD_ha"]], left_index=True, right_index=True)
        res = pd.merge(res, df_mj, left_index=True, right_index=True)
        res = pd.merge(res, df_mj_ha, left_index=True, right_index=True)
        res["diff_ghd"] =  res["GHD_ha"]/res["GHD_og"]
        res["diff_mj"] =  res["multijoin_ha"]/res["multijoin_og"]
        row = {"Pattern": p, "Mean factor mj":  round(res["diff_mj"].mean(), 2), "Mean factor ghd": round(res["diff_ghd"].mean(), 2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/qdag_variant_factor.csv", index=False)


def yk_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "bowtie"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"Pattern": [], "Mean difference": [], "Median difference": [], "Max difference": []}
    df = pd.DataFrame(data)
    data = {"GHD": [], "GHD np": [], "diff": []}
    tdf = pd.DataFrame(data)
    
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD"] = yk_res.min(axis=1)
            df1np = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_1.csv", names=["time"])
            df2np = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_2.csv", names=["time"])
            df3np = pd.read_csv(f"outputs_time/no_pruning_{p}_ghd_yk_3.csv", names=["time"])

            ykp_res = pd.merge(df1np, df2np, left_index=True, right_index=True)
            ykp_res = pd.merge(ykp_res, df3np, left_index=True, right_index=True)
            ykp_res["GHD np"] = ykp_res.min(axis=1)
        else:
            yk_res = pd.read_csv(f"outputs_time/{p}_yk.csv", names=["GHD"])
            ykp_res = pd.read_csv(f"outputs_time/no_pruning_{p}_yk.csv", names=["GHD np"])

        res = pd.merge(yk_res[["GHD"]], ykp_res[["GHD np"]], left_index=True, right_index=True)
        res["diff"] = 100*(1 - res["GHD"] / res["GHD np"])
        row = {"Pattern": p, "Mean difference": round(res["diff"].mean(),2), "Median difference": round(res["diff"].median(),2), "Max difference":round(res["diff"].max(),2)}
        df.loc[len(df)] = row
        tdf=pd.concat([tdf, res], ignore_index=True)
    df.to_csv("outputs/pruning_percentages.csv", index=False)
    fig = plt.figure(layout='constrained', figsize=(10, 10))
    fig.suptitle('Percentage change in time when using pruning')
    plt.axvline(linewidth=2, color='r')
    tdf["diff"].hist(bins=10)
    print(tdf)
    plt.savefig("outputs/pruning_diff")

def bpt():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "bowtie"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"average": [], "median": []}
    df = pd.DataFrame(data)
    data = {"tuples": [], "qdags": [], "ratio":[]}
    res =pd.DataFrame(data)
    for i, p in enumerate(patterns):
        print(p)
        if p in multi:
            df1 = pd.read_csv(f"outputs_space/{p}_ghd_yk_1.csv")
        else:
            df1 = pd.read_csv(f"outputs_space/{p}_yk_1.csv")
        df1["ratio"]=df1.qdags/df1.tuples
        res = pd.concat([res, df1[["tuples", "qdags", "ratio"]]])
    row = {"average": round( res["ratio"].mean(),2), "median": round( res["ratio"].median(),2)}
    df.loc[len(df)] = row
    df.to_csv("outputs/bpt.csv", index=False)

def yk_space():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "bowtie"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"] 
    data = {"Pattern": [], "Avg factor input": [], "Median factor input": [], "Avg factor inter": [], "Median factor inter": []}
    df = pd.DataFrame(data)
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_space/{p}_ghd_yk_1.csv")
            df2 = pd.read_csv(f"outputs_space/{p}_ghd_yk_2.csv")
            df3 = pd.read_csv(f"outputs_space/{p}_ghd_yk_3.csv")

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res[['qdags_1','post mj_1','post mj_2','post mj', 'result']].to_csv(f'outputs/{p}_sizes.csv', index=False)
            yk_res["input"] = yk_res['qdags_1']/yk_res['result_1']
            yk_res=yk_res.assign(inter=lambda d: d[['post mj_1','post mj_2','post mj']].min(1)/yk_res['result_1'])
        else:
            yk_res = pd.read_csv(f"outputs_space/{p}_yk_1.csv")
            yk_res[['qdags','post mj','result']].to_csv(f'outputs/{p}_sizes.csv', index=False)
            yk_res["input"] = yk_res['qdags']/yk_res['result']
            yk_res["inter"] = yk_res['post mj']/yk_res['result']
            #qdags, post mj size, result size }
        row = {"Pattern": p, "Avg factor input": round( yk_res["input"].mean(),2), "Median factor input": round( yk_res["input"].median(),2), "Avg factor inter": round( yk_res["inter"].mean(),2), "Median factor inter": round( yk_res["inter"].median(),2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/avg_size.csv", index=False)
    

if __name__ == '__main__':
    yk_space()
