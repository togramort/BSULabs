FROM mcr.microsoft.com/dotnet/runtime:5.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["linq_pets/linq_pets.csproj", "linq_pets/"]
RUN dotnet restore "linq_pets/linq_pets.csproj"
COPY . .
WORKDIR "/src/linq_pets"
RUN dotnet build "linq_pets.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "linq_pets.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "linq_pets.dll"]
