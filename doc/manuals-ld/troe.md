# Temporal Representation of Entities
Starting with the Orion-LD release [Beta 2](github...), Orion-LD implements Temporal Representation of Entities (TRoE),
in an experimental state.
The feature is minimally tested and not production-ready, but more or less working and the development
team would be more than happy to have it tested, and any found bugs reported.

The sink used for TRoE is Postgres, with TimescaleDB extension.

While Orion-LD takes care of populating the TRoE databases, another component handles the queries of temporal data - [Mintaka](https://github.com/FIWARE/Mintaka).
To install Mintaka, follow the instructions in the [Installation Guide](https://github.com/FIWARE/Mintaka/docs/installation-guide.md).

So, for queries of the temporal data, instead of sending the requests to Orion-LD, on (default) port 1026, the queries are sent to Mintaka, on (default) port xxxx.