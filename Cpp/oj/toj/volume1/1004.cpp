#include <iostream>
#include <algorithm>
using namespace std;

struct street {
	int x, y;
	int number;
	int nextx, nexty;
	int prev, next;
} streets[2048];
int junctions[64];
int path(int junction, int *start_street, int *end_street) {
	int street, s;
	street = -1;
	for (;;) {
		if ((s = junctions[junction]) == -1) {
			if (street == -1)
				*start_street = -1;
			*end_street = street;
			return junction;
		}
		if (streets[s].next == -1) {
			if (street == -1) {
				streets[s].prev = -2;
				*start_street = s;
			} else {
				streets[s].prev = street;
				streets[street].next = s;
			}
			streets[s].next = -2;
			junction = (streets[s].x != junction) ? streets[s].x : streets[s].y;
			street = s;
		} else {
			junctions[junction] = (streets[s].x == junction) ? streets[s].nextx
					: streets[s].nexty;
		}
	}
}

int number_cmp(const void *a, const void *b) {
	return ((struct street *) a)->number - ((struct street *) b)->number;
}

void print(int start_street) {
	int s;
	cout << streets[start_street].number;
	for (s = streets[start_street].next; s != start_street; s = streets[s].next)
		cout << " " << streets[s].number;
	cout << endl << endl;
}

int main() {
	int count, junction, start_street, street, i, s, e, ss;
	for (;;) {
		count = 0;
		for (;;) {
			cin >> streets[count].x >> streets[count].y;
			if (!streets[count].x || !streets[count].y)
				break;
			cin >> streets[count++].number;
		}

		if (!count)
			break;
		junction = min(streets[0].x, streets[0].y);
		qsort(streets, count, sizeof(streets[0]), number_cmp);
		memset(junctions, -1, sizeof(junctions));
		for (i = count - 1; i >= 0; i--) {
			streets[i].nextx = junctions[streets[i].x];
			junctions[streets[i].x] = i;
			streets[i].nexty = junctions[streets[i].y];
			junctions[streets[i].y] = i;
			streets[i].prev = -1;
			streets[i].next = -1;
		}

		if (path(junction, &start_street, &e) != junction)
			goto fail;
		streets[start_street].prev = e;
		streets[e].next = start_street;
		street = start_street;
		do {
			if (path(junction, &s, &e) != junction)
				goto fail;
			if (s != -1 && e != -1) {
				ss = streets[street].prev;
				streets[s].prev = ss;
				streets[ss].next = s;
				streets[street].prev = e;
				streets[e].next = street;
			}
			street = streets[street].prev;
			junction = (streets[street].x != junction) ? streets[street].x
					: streets[street].y;
		} while (street != start_street);
		print(start_street);
		continue;
		fail: cout << "Round trip does not exist.\n\n";
	}
	return 0;
}

