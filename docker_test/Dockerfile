FROM ubuntu:18.04
LABEL maintainer="Daniil Belinskiy"
LABEL description="Samuel L. Jackson container"
RUN apt-get update && apt-get install -y python3
COPY README /README
COPY Jackson /Jackson
WORKDIR /Jackson
CMD cat /README && python3 /Jackson/Jackson.py
