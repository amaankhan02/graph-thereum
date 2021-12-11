from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def plot(filepath):
  df = pd.read_csv(filepath)
  x = df['incident_edges'].to_numpy()
  y = df['betweenness_centrality'].to_numpy()
  xy = np.vstack([x, y])
  z = gaussian_kde(xy)(xy)

  plt.scatter(x, y, c=z)
  plt.xscale('log')
  plt.title('Betweenness Centrality as a\nFunction of Incident Edges')
  plt.xlabel('Incident Edges (log)')
  plt.ylabel('Betweenness Centrality')
  plt.colorbar()
  plt.show()

plot('data/30mb_betweenness_centrality.csv')