## Procedure for doulbe check signal efficiency in hadronic channel

```
$ svn checkout https://github.com/ywkao/tprimetH/branches/re-reco/validation
$ cd validation/
$ time ./run.py 2>&1 | tee log.txt
$ ./convert.py
$ vim make_efficiency_plots.py # search "collection_efficiency" for double check
$ ./make_efficiency_plots.py # make plots
```
