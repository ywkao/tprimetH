## Procedure for doulbe check signal efficiency in hadronic channel

```
$ time ./run.py 2>&1 | tee log.txt
$ ./convert.py
$ vim ../obtain_mass.py # search "collection_efficiency"
```
