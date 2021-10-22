import networkx as nx
import tempfile
import sys
import datetime as dt
import random as r
import argparse

original_stdout = sys.stdout

def random_graph(args):
    now = dt.datetime.now()
    print('Generating random graph instances...')
    timestamp = f'{now.year}{now.month}{now.day}{now.hour}{now.minute}'
    filename = f'{timestamp}RANDOM{args.i}n{args.n}p{args.p}s{args.seed}'.replace('.', '-')
    if (args.f is None):
        args.f = 'g6'
    filename += '.' + args.f
    if (args.i is None):
        args.i = 1
    with open(filename, "w") as fh:
        for s in range(args.i):
            G = nx.fast_gnp_random_graph(args.n, args.p, seed=args.seed+s)
            with tempfile.NamedTemporaryFile() as f:
                if (args.f == 's6'):
                    nx.write_sparse6(G, f.name, header=False)
                else:
                    nx.write_graph6(G, f.name, G, header=False)
                _ = f.seek(0)
                print(f.read().decode(), file=fh, end='')
    print('Outputfile:' + filename)
    print('Done')

def clique(args):
    now = dt.datetime.now()
    print('Generating clique instances...')
    if (args.i is None):
        args.i = args.n
    elif (args.i < args.n):
        args.i, args.n = args.n, args.i 
    timestamp = f'{now.year}{now.month}{now.day}{now.hour}{now.minute}'
    filename = f'{timestamp}CLIQUE{args.n}to{args.i}'.replace('.', '-')
    filename += '.g6'
    with open(filename, "w") as fh:
        for s in range(args.n, args.i+1):
            G = nx.complete_graph(s)
            with tempfile.NamedTemporaryFile() as f:
                nx.write_graph6(G, f.name, header=False)
                _ = f.seek(0)
                print(f.read().decode(), file=fh, end='')
    print('Outputfile:' + filename)
    print('Done')

def check_int(value):
    num = int(value)
    if num < 0:
        raise argparse.ArgumentTypeError("%s must be between 0 and 1" % value)
    return num

def check_probability(value):
    prob = float(value)
    if prob > 1 or prob < 0:
        raise argparse.ArgumentTypeError("%s must be between 0 and 1" % value)
    return prob

parser = argparse.ArgumentParser(prog='#k-Paths Test Graph Generator', usage='%(prog)s', 
description='Generate cliques or graphs following the Erdős-Rényi random graph model')
subparsers = parser.add_subparsers(help='sub-command help')

parser_r = subparsers.add_parser('random', help='random graphs')
parser_r.add_argument('-i', type=check_int, metavar='', default=1, help='number of graphs')
parser_r.add_argument('n', type=check_int, metavar='n', help='number of vertices')
parser_r.add_argument('p', type=check_probability, metavar='p', help='edge probability')
parser_r.add_argument('-s', '--seed', type=check_int, metavar='', default=r.randint(0,9999), 
    help='start of random number sequence')
parser_r.add_argument('-f', type=str, choices=['g6','s6','d6'], 
    help='undirected (g6), sparse (s6)')
parser_r.set_defaults(func=random_graph)

parser_c = subparsers.add_parser('clique')
parser_c.add_argument('n', type=check_int, help='number of vertices')
parser_c.add_argument('-i', type=check_int, metavar='', help='generate Kn to Ki')
parser_c.set_defaults(func=clique)

if __name__ == '__main__':
    args = parser.parse_args()
    args.func(args)
