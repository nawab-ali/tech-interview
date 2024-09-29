#!/home/ubuntu/wspace-2/anaconda2/bin/python

from collections import defaultdict

def group_cities_by_state():
    cities_by_state = defaultdict(list)

    city_list = [('TX','Austin'), ('TX','Houston'), ('NY','Albany'),
                 ('NY', 'Syracuse'), ('NY', 'Buffalo'), ('NY', 'Rochester'),
                 ('TX', 'Dallas'), ('CA','Sacramento'), ('CA', 'Palo Alto'),
                 ('GA', 'Atlanta')]

    for state, city in city_list:
        cities_by_state[state].append(city)

    for state in cities_by_state.keys():
        print state, ': ', cities_by_state[state]

def main():
    group_cities_by_state()

if __name__ == '__main__':
    main()
