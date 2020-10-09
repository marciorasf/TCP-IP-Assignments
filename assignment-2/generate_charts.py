# Before running this script, make sure the CSVs of every result is available on this folder

# %% imports
import pandas as pd
import plotly.express as px
import numpy as np
import os

# %% declare params and functions
simulation_labels = ["sim_1", "sim_2", "sim_3"]
df_labels = ["size"] + simulation_labels


def generate_test_a_chart(filename, chart_title, output_filename):
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

    save_chart_on_file(chart, output_filename)


def generate_test_b_chart(filename, chart_title, output_filename):
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

    save_chart_on_file(chart, output_filename)


def create_images_folder():
    if not os.path.exists("images"):
        os.mkdir("images")

def save_chart_on_file(chart, output_filename):
    try:
        chart.write_image('images/{}'.format(output_filename))
    except:
        chart.show()

# %% generate charts
test_a_filename = "test_a_rtt_in_ms.csv"
test_b_filename = "test_b_throughput_in_bits_per_second.csv"


create_images_folder()
generate_test_a_chart(test_a_filename, "Teste A - RTT", "test_a.png")
generate_test_b_chart(test_b_filename, "Teste B - Vazão", "test_b.png")
