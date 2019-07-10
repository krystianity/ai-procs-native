FROM aip:local
ADD ./metadata.json /aip/metadata.json
ADD ./model.pt /aip/model.pt
ENTRYPOINT ["/aip/aip-server", "./metadata.json", "./model.pt"]