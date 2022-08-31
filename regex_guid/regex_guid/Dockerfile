FROM mcr.microsoft.com/dotnet/runtime:5.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["regex_guid/regex_guid.csproj", "regex_guid/"]
RUN dotnet restore "regex_guid/regex_guid.csproj"
COPY . .
WORKDIR "/src/regex_guid"
RUN dotnet build "regex_guid.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "regex_guid.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "regex_guid.dll"]
