FROM mcr.microsoft.com/dotnet/runtime:5.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["linq2/linq2.csproj", "linq2/"]
RUN dotnet restore "linq2/linq2.csproj"
COPY . .
WORKDIR "/src/linq2"
RUN dotnet build "linq2.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "linq2.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "linq2.dll"]
