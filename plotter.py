import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

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
    data = {"Pattern": [], "Mean MJ": [], "Median MJ": [], "Std. dev. MJ": [], "Mean GHD": [], "Median GHD": [], "Std. dev. GHD": []}
    df = pd.DataFrame(data)
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
        row = {"Pattern": p, "Mean MJ": round(res.multijoin.mean(),2), "Median MJ": round(res.multijoin.median(),2), "Std. dev. MJ": round(res.multijoin.std(),2), "Mean GHD": round(res.GHD.mean(),2), "Median GHD": round(res.GHD.median(),2), "Std. dev. GHD": round(res.GHD.std(),2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/ha_times_stats.csv", index=False)

    handles, labels = plt.gca().get_legend_handles_labels()
    fig.legend(handles, labels, loc='upper center')
    plt.savefig("outputs/times")

def yk_times():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
   
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"Pattern": [], "Mean difference": [], "Median difference": [], "Most  hindrance": [], "Most improvement": []}
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
        row = {"Pattern": p, "Mean difference": round(res["diff"].mean(),2), "Median difference": round(res["diff"].median(),2), "Most  hindrance":round(res["diff"].min(),2), "Most improvement":round(res["diff"].max(),2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/ha_percentages.csv", index=False)
        
def timeouts():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    data = {"Pattern": [], "Number of timeouts": [], "Average query time for GHD [s]": []}
    df = pd.DataFrame(data)
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_1.csv", names=["time"])
            df2 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_2.csv", names=["time"])
            df3 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_3.csv", names=["time"])

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res["GHD"] = yk_res.min(axis=1)
            df_mj = pd.read_csv(f"outputs_time/ha_{p}_ghd_mj.csv", names=["multijoin"])
        else:
            yk_res = pd.read_csv(f"outputs_time/ha_{p}_yk.csv", names=["GHD"])
            df_mj = pd.read_csv(f"outputs_time/ha_{p}_mj.csv", names=["multijoin"])

        res = pd.merge(yk_res[["GHD"]], df_mj, left_index=True, right_index=True)
        if "timeout" in res.multijoin.unique():
            row = {"Pattern": p, "Number of timeouts": len(res[res.multijoin=="timeout"]), "Average query time for GHD [s]": round(res[res.multijoin=="timeout"].GHD.mean(),2)}
            df.loc[len(df)] = row
    df.to_csv("outputs/ha_timeouts.csv", index=False)
   
def size_config():
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]
    medianprops = dict(linestyle='-.', linewidth=2.5, color='black')
    rdict = {}
    for i, m in enumerate(multi):
        df1 = pd.read_csv(f"outputs_space/results_ha_{m}_ghd_yk_1.csv")
        df2 = pd.read_csv(f"outputs_space/results_ha_{m}_ghd_yk_2.csv")
        df3 = pd.read_csv(f"outputs_space/results_ha_{m}_ghd_yk_3.csv")
        df1["config"]=1
        df2["config"]=2
        df3["config"]=3 
        df1['query'] = np.arange(1, df1.shape[0] + 1)
        df2['query'] = np.arange(1, df2.shape[0] + 1)
        df3['query'] = np.arange(1, df3.shape[0] + 1)
        res = pd.concat([df1,df2,df3])
        res["tuples per node"]=res["tuples per node"].str.strip("()").str.split('-')
        res["post mj results"]=res["post mj results"].str.strip("()").str.split('-').map(lambda x: int(x[0])+int(x[1]))
        smallest = list(res.sort_values('post mj results', ascending=False).groupby('query').head(1).sort_values('query').config)
        print(m, smallest)
        tdf1 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_1.csv", names=["time"])
        tdf2 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_2.csv", names=["time"])
        tdf3 = pd.read_csv(f"outputs_time/ha_{m}_ghd_yk_3.csv", names=["time"])
        tdf1["config"]=1
        tdf2["config"]=2
        tdf3["config"]=3 
        tdf1['query'] = np.arange(1, tdf1.shape[0] + 1)
        tdf2['query'] = np.arange(1, tdf2.shape[0] + 1)
        tdf3['query'] = np.arange(1, tdf3.shape[0] + 1)
        tres = pd.concat([tdf1,tdf2,tdf3])
        fastest = list(tres.sort_values('time', ascending=False).groupby('query').head(1).sort_values('query', ascending=False).config)
        rdict[m]=sum(x == y for x, y in zip(smallest, fastest))/len(df1)
    print(rdict)
    #{'J3': 0.6, 'J4': 0.46, 'T3': 0.52, 'Ti3': 0.36, 'T4': 0.7, 'Ti4': 0.7551020408163265}
    #largest is slowest {'J3': 0.2, 'J4': 0.26, 'T3': 0.22, 'Ti3': 0.22, 'T4': 0.3, 'Ti4': 0.49}


def number_of_results():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
    data = {"Pattern": [], "Avg Results": [], "Median Results": []}
    df = pd.DataFrame(data)
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"]

    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_space/ha_{p}_ghd_yk_1.csv")
        else:
            df1 = pd.read_csv(f"outputs_space/ha_{p}_yk_1.csv")
        row = {"Pattern": p, "Avg Results": round(df1["number of results"].mean(),2), "Median Results":  round(df1["number of results"].median(),2)}
        df.loc[len(df)] = row
    df.to_csv("outputs/number_results.csv", index=False)


def yk_space():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"] 
    data = {"Pattern": [], "Avg factor input": [], "Median factor input": [], "Avg factor inter": [], "Median factor inter": []}
    df = pd.DataFrame(data)
    for i, p in enumerate(patterns):
        temp = {"input":[],"inter":[]}
        df_temp = pd.DataFrame(temp)
        if p in multi:
            tdf1 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_1.csv", names=["time"])
            tdf2 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_2.csv", names=["time"])
            tdf3 = pd.read_csv(f"outputs_time/ha_{p}_ghd_yk_3.csv", names=["time"])
            tdf1["config"]=1
            tdf2["config"]=2
            tdf3["config"]=3 
            tdf1['query'] = np.arange(0, tdf1.shape[0] )
            tdf2['query'] = np.arange(0, tdf2.shape[0] )
            tdf3['query'] = np.arange(0, tdf3.shape[0] )
            tres = pd.concat([tdf1,tdf2,tdf3])
            fastest = list(tres.sort_values('time', ascending=True).groupby('query').head(1).sort_values('query').config)
            df1 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_1.csv")
            df2 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_2.csv")
            df3 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_3.csv")
            df1['query'] = np.arange(0, df1.shape[0] )
            df2['query'] = np.arange(0, df2.shape[0] )
            df3['query'] = np.arange(0, df3.shape[0] )
            for i,f in enumerate(fastest):
                if f==1:
                    aux_input = df1[df1['query']==i]['qdags'].values[0]
                    aux_res = df1[df1['query']==i]['result size'].values[0]
                    aux_inter = df1[df1['query']==i]['post mj size'].values[0]
                elif f==2:
                    aux_input = df2[df2['query']==i]['qdags'].values[0]
                    aux_res = df2[df2['query']==i]['result size'].values[0]
                    aux_inter = df2[df2['query']==i]['post mj size'].values[0]
                elif f==3:
                    aux_input = df3[df3['query']==i]['qdags'].values[0]
                    aux_res = df3[df3['query']==i]['result size'].values[0]
                    aux_inter = df3[df3['query']==i]['post mj size'].values[0]
                row = {"input":aux_input/aux_res,"inter":[], "inter":aux_inter/aux_res}
                df_temp.loc[len(df_temp)] = row
            row = {"Pattern": p, "Avg factor input": round( df_temp["input"].mean(),2), "Median factor input": round( df_temp["input"].median(),2), "Avg factor inter": round(df_temp["inter"].mean(),2), "Median factor inter": round(df_temp["inter"].median(),2)}
            df.loc[len(df)] = row
        else:
            yk_res = pd.read_csv(f"outputs_space/ha_{p}_yk.csv")
            yk_res["input"] = yk_res['qdags']/yk_res['result']
            yk_res["inter"] = yk_res['post mj']/yk_res['result']
            row = {"Pattern": p, "Avg factor input": round( yk_res["input"].mean(),2), "Median factor input": round( yk_res["input"].median(),2), "Avg factor inter": round(yk_res["inter"].mean(),2), "Median factor inter": round(yk_res["inter"].median(),2)}
            df.loc[len(df)] = row
        
    df.to_csv("outputs/avg_size.csv", index=False)

'''
            df1 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_1.csv")
            df2 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_2.csv")
            df3 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_3.csv")
            df1["config"]=1
            df2["config"]=2
            df3["config"]=3 
            

            yk_res = pd.merge(df1, df2, left_index=True, right_index=True, suffixes=('_1', '_2'))
            yk_res = pd.merge(yk_res, df3, left_index=True, right_index=True)
            yk_res[['qdags_1','post mj size_1','post mj size_2','post mj size', 'result size_1']].to_csv(f'outputs/{p}_sizes.csv', index=False)
            yk_res["input"] = yk_res['qdags_1']/yk_res['result size_1']
            yk_res=yk_res.assign(inter=lambda d: d[['post mj size_1','post mj size_2','post mj size']].min(1)/yk_res['result size_1'])'''


def bpt():
    patterns = ["J3", "J4", "T3", "Ti3", "T4", "Ti4", "triangle_tadpole", "square_tadpole", "bowtie", "triangle_barbell", "square_barbell", "penta_barbell"]
    multi = ["J3", "J4", "T3", "Ti3", "T4", "Ti4"] 
    data = {"average": [], "median": []}
    df = pd.DataFrame(data)
    data = {"tuples": [], "qdags": [], "ratio":[]}
    res =pd.DataFrame(data)
    for i, p in enumerate(patterns):
        if p in multi:
            df1 = pd.read_csv(f"outputs_space/results_ha_{p}_ghd_yk_1.csv")
        else:
            df1 = pd.read_csv(f"outputs_space/ha_{p}_yk.csv")
        df1["ratio"]=df1.qdags/df1.tuples
        res = pd.concat([res, df1[["tuples", "qdags", "ratio"]]])
    row = {"average": round( res["ratio"].mean(),2), "median": round( res["ratio"].median(),2)}
    df.loc[len(df)] = row
    df.to_csv("outputs/bpt.csv", index=False)
       
if __name__ == '__main__':
    yk_space()