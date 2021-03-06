# Before running this script, make sure the CSVs of every result is available on this folder

# %% imports
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px
import numpy as np

# %% declare params and functions
simulation_labels = ["sim_1", "sim_2", "sim_3"]
df_labels = ["size"] + simulation_labels


def generate_test_a_chart(filename, chart_title):
    x_nticks = 40
    y_nticks = 25

    df = pd.read_csv(filename, index_col=0, header=None, names=df_labels)

    df["mean"] = df[simulation_labels].mean(axis=1)

    chart = px.line(df, y="mean")
    chart.update_layout(
        title={
            "text": chart_title,
            "x": 0.5
        },
        xaxis={
            "title": "Tamanho das mensagens [B]",
            "nticks": x_nticks
        },
        yaxis={
            "title": "RTT [ms]",
            "nticks": y_nticks
        }
    )
    chart.show()


def generate_test_b_chart(filename, chart_title):
    x_nticks = 40
    y_nticks = 25

    df = pd.read_csv(
        filename, index_col=0, header=None, names=df_labels)

    df["mean"] = df[simulation_labels].mean(axis=1)
    df = df.set_index(np.array((df.index.values / 1024), dtype=np.int32))

    chart = px.line(df, y="mean")
    chart.update_layout(
        title={
            "text": chart_title,
            'x': 0.5,
        },
        xaxis={
            "title": "Tamanho das mensagens [kB]",
            "nticks": x_nticks
        },
        yaxis={
            "title": "Vazão [b/s]",
            "nticks": y_nticks
        }
    )
    chart.show()


# %% generate charts
tcp_test_a_filename = "tcp_test_a_rtt_in_ms.csv"
tcp_test_b_filename = "tcp_test_b_throughput_in_bits_per_second.csv"

generate_test_a_chart(tcp_test_a_filename, "Teste A - RTT utilizando socket TCP")
generate_test_b_chart(tcp_test_b_filename, "Teste B - Vazão utilizando socket TCP")

udp_test_a_filename = "udp_test_a_rtt_in_ms.csv"
udp_test_b_filename = "udp_test_b_throughput_in_bits_per_second.csv"

generate_test_a_chart(udp_test_a_filename, "Teste A - RTT utilizando socket UDP")
generate_test_b_chart(udp_test_b_filename, "Teste B - Vazão utilizando socket UDP")
