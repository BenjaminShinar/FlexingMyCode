#include "identifiers/mockmon_species_id.h"

#include <iostream>


//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{
    std::string speciesToStr(const MockmonSpeciesId speceis)
    {
        switch (speceis)
        {
        case MockmonSpeciesId::Bulbasaur: return "Bulbasaur"; break;
        case MockmonSpeciesId::Ivysaur: return "Ivysaur"; break;
        case MockmonSpeciesId::Venusaur: return "Venusaur"; break;
        case MockmonSpeciesId::Charmander: return "Charmander"; break;
        case MockmonSpeciesId::Charmeleon: return "Charmeleon"; break;
        case MockmonSpeciesId::Charizard: return "Charizard"; break;
        case MockmonSpeciesId::Squirtle: return "Squirtle"; break;
        case MockmonSpeciesId::Wartortle: return "Wartortle"; break;
        case MockmonSpeciesId::Blastoise: return "Blastoise"; break;
        case MockmonSpeciesId::Caterpie: return "Caterpie"; break;
        case MockmonSpeciesId::Metapod: return "Metapod"; break;
        case MockmonSpeciesId::Butterfree: return "Butterfree"; break;
        case MockmonSpeciesId::Weedle: return "Weedle"; break;
        case MockmonSpeciesId::Kakuna: return "Kakuna"; break;
        case MockmonSpeciesId::Beedrill: return "Beedrill"; break;
        case MockmonSpeciesId::Pidgey: return "Pidgey"; break;
        case MockmonSpeciesId::Pidgeotto: return "Pidgeotto"; break;
        case MockmonSpeciesId::Pidgeot: return"Pidgeot"; break;
        case MockmonSpeciesId::Rattata: return"Rattata"; break;
        case MockmonSpeciesId::Raticate: return "Raticate"; break;
        case MockmonSpeciesId::Spearow: return "Spearow"; break;
        case MockmonSpeciesId::Fearow: return "Fearow"; break;
        case MockmonSpeciesId::Ekans: return "Ekans"; break;
        case MockmonSpeciesId::Arbok: return "Arbok"; break;
        case MockmonSpeciesId::Pikachu: return "Pikachu"; break;
        case MockmonSpeciesId::Raichu: return "Raichu"; break;
        case MockmonSpeciesId::Sandshrew: return "Sandshrew"; break;
        case MockmonSpeciesId::Sandslash: return "Sandslash"; break;
        case MockmonSpeciesId::Nidoran_Female: return "Nidoran Female ♀"; break;
        case MockmonSpeciesId::Nidorina: return "Nidorina"; break;
        case MockmonSpeciesId::Nidoqueen: return "Nidoqueen"; break;
        case MockmonSpeciesId::Nidoran_Male: return "Nidoran Male ♂"; break;
        case MockmonSpeciesId::Nidorino: return "Nidorino"; break;
        case MockmonSpeciesId::Nidoking: return "Nidoking"; break;
        case MockmonSpeciesId::Clefairy: return "Clefairy"; break;
        case MockmonSpeciesId::Clefable: return "Clefable"; break;
        case MockmonSpeciesId::Vulpix: return "Vulpix"; break;
        case MockmonSpeciesId::Ninetales: return "Ninetales"; break;
        case MockmonSpeciesId::Jigglypuff: return "Jigglypuff"; break;
        case MockmonSpeciesId::Wigglytuff: return "Wigglytuff"; break;
        case MockmonSpeciesId::Zubat: return "Zubat"; break;
        case MockmonSpeciesId::Golbat: return "Golbat"; break;
        case MockmonSpeciesId::Oddish: return "Oddish"; break;
        case MockmonSpeciesId::Gloom: return "Gloom"; break;
        case MockmonSpeciesId::Vileplume: return "Vileplume"; break;
        case MockmonSpeciesId::Paras: return "Paras"; break;
        case MockmonSpeciesId::Parasect: return "Parasect"; break;
        case MockmonSpeciesId::Venonat: return "Venonat"; break;
        case MockmonSpeciesId::Venomoth: return "Venomoth"; break;
        case MockmonSpeciesId::Diglett: return "Diglett"; break;
        case MockmonSpeciesId::Dugtrio: return "Dugtrio"; break;
        case MockmonSpeciesId::Meowth: return "Meowth"; break;
        case MockmonSpeciesId::Persian: return "Persian"; break;
        case MockmonSpeciesId::Psyduck: return "Psyduck"; break;
        case MockmonSpeciesId::Golduck: return "Golduck"; break;
        case MockmonSpeciesId::Mankey: return "Mankey"; break;
        case MockmonSpeciesId::Primeape: return "Primeape"; break;
        case MockmonSpeciesId::Growlithe: return "Growlithe"; break;
        case MockmonSpeciesId::Arcanine: return "Arcanine"; break;
        case MockmonSpeciesId::Poliwag: return "Poliwag"; break;
        case MockmonSpeciesId::Poliwhirl: return "Poliwhirl"; break;
        case MockmonSpeciesId::Poliwrath: return "Poliwrath"; break;
        case MockmonSpeciesId::Abra: return "Abra"; break;
        case MockmonSpeciesId::Kadabra: return "Kadabra"; break;
        case MockmonSpeciesId::Alakazam: return "Alakazam"; break;
        case MockmonSpeciesId::Machop: return "Machop"; break;
        case MockmonSpeciesId::Machoke: return "Machoke"; break;
        case MockmonSpeciesId::Machamp: return "Machamp"; break;
        case MockmonSpeciesId::Bellsprout: return "Bellsprout"; break;
        case MockmonSpeciesId::Weepinbell: return "Weepinbell"; break;
        case MockmonSpeciesId::Victreebel: return "Victreebel"; break;
        case MockmonSpeciesId::Tentacool: return "Tentacool"; break;
        case MockmonSpeciesId::Tentacruel: return "Tentacruel"; break;
        case MockmonSpeciesId::Geodude: return "Geodude"; break;
        case MockmonSpeciesId::Graveler: return "Graveler"; break;
        case MockmonSpeciesId::Golem: return "Golem"; break;
        case MockmonSpeciesId::Ponyta: return "Ponyta"; break;
        case MockmonSpeciesId::Rapidash: return "Rapidash"; break;
        case MockmonSpeciesId::Slowpoke: return "Slowpoke"; break;
        case MockmonSpeciesId::Slowbro: return "Slowbro"; break;
        case MockmonSpeciesId::Magnemite: return "Magnemite"; break;
        case MockmonSpeciesId::Magneton: return "Magneton"; break;
        case MockmonSpeciesId::Farfetchd: return "Farfetch\'d"; break;
        case MockmonSpeciesId::Doduo: return "Doduo"; break;
        case MockmonSpeciesId::Dodrio: return "Dodrio"; break;
        case MockmonSpeciesId::Seel: return "Seel"; break;
        case MockmonSpeciesId::Dewgong: return "Dewgong"; break;
        case MockmonSpeciesId::Grimer: return "Grimer"; break;
        case MockmonSpeciesId::Muk: return "Muk"; break;
        case MockmonSpeciesId::Shellder: return "Shellder"; break;
        case MockmonSpeciesId::Cloyster: return "Cloyster"; break;
        case MockmonSpeciesId::Gastly: return "Gastly"; break;
        case MockmonSpeciesId::Haunter: return "Haunter"; break;
        case MockmonSpeciesId::Gengar: return "Gengar"; break;
        case MockmonSpeciesId::Onix: return "Onix"; break;
        case MockmonSpeciesId::Drowzee: return "Drowzee"; break;
        case MockmonSpeciesId::Hypno: return "Hypno"; break;
        case MockmonSpeciesId::Krabby: return "Krabby"; break;
        case MockmonSpeciesId::Kingler: return "Kingler"; break;
        case MockmonSpeciesId::Voltorb: return "Voltorb"; break;
        case MockmonSpeciesId::Electrode: return "Electrode"; break;
        case MockmonSpeciesId::Exeggcute: return "Exeggcute"; break;
        case MockmonSpeciesId::Exeggutor: return "Exeggutor"; break;
        case MockmonSpeciesId::Cubone: return "Cubone"; break;
        case MockmonSpeciesId::Marowak: return "Marowak"; break;
        case MockmonSpeciesId::Hitmonlee: return "Hitmonlee"; break;
        case MockmonSpeciesId::Hitmonchan: return "Hitmonchan"; break;
        case MockmonSpeciesId::Lickitung: return "Lickitung"; break;
        case MockmonSpeciesId::Koffing: return "Koffing"; break;
        case MockmonSpeciesId::Weezing: return "Weezing"; break;
        case MockmonSpeciesId::Rhyhorn: return "Rhyhorn"; break;
        case MockmonSpeciesId::Rhydon: return "Rhydon"; break;
        case MockmonSpeciesId::Chansey: return "Chansey"; break;
        case MockmonSpeciesId::Tangela: return "Tangela"; break;
        case MockmonSpeciesId::Kangaskhan: return "Kangaskhan"; break;
        case MockmonSpeciesId::Horsea: return "Horsea"; break;
        case MockmonSpeciesId::Seadra: return "Seadra"; break;
        case MockmonSpeciesId::Goldeen: return "Goldeen"; break;
        case MockmonSpeciesId::Seaking: return "Seaking"; break;
        case MockmonSpeciesId::Staryu: return "Staryu"; break;
        case MockmonSpeciesId::Starmie: return "Starmie"; break;
        case MockmonSpeciesId::MrMime: return "Mr. Mime"; break;
        case MockmonSpeciesId::Scyther: return "Scyther"; break;
        case MockmonSpeciesId::Jynx: return "Jynx"; break;
        case MockmonSpeciesId::Electabuzz: return "Electabuzz"; break;
        case MockmonSpeciesId::Magmar: return "Magmar"; break;
        case MockmonSpeciesId::Pinsir: return "Pinsir"; break;
        case MockmonSpeciesId::Tauros: return "Tauros"; break;
        case MockmonSpeciesId::Magikarp: return "Magikarp"; break;
        case MockmonSpeciesId::Gyarados: return "Gyarados"; break;
        case MockmonSpeciesId::Lapras: return "Lapras"; break;
        case MockmonSpeciesId::Ditto: return "Ditto"; break;
        case MockmonSpeciesId::Eevee: return "Eevee"; break;
        case MockmonSpeciesId::Vaporeon: return "Vaporeon"; break;
        case MockmonSpeciesId::Jolteon: return "Jolteon"; break;
        case MockmonSpeciesId::Flareon: return "Flareon"; break;
        case MockmonSpeciesId::Porygon: return "Porygon"; break;
        case MockmonSpeciesId::Omanyte: return "Omanyte"; break;
        case MockmonSpeciesId::Omastar: return "Omastar"; break;
        case MockmonSpeciesId::Kabuto: return "Kabuto"; break;
        case MockmonSpeciesId::Kabutops: return "Kabutops"; break;
        case MockmonSpeciesId::Aerodactyl: return "Aerodactyl"; break;
        case MockmonSpeciesId::Snorlax: return "Snorlax"; break;
        case MockmonSpeciesId::Articuno: return "Articuno"; break;
        case MockmonSpeciesId::Zapdos: return "Zapdos"; break;
        case MockmonSpeciesId::Moltres: return "Moltres"; break;
        case MockmonSpeciesId::Dratini: return "Dratini"; break;
        case MockmonSpeciesId::Dragonair: return "Dragonair"; break;
        case MockmonSpeciesId::Dragonite: return "Dragonite"; break;
        case MockmonSpeciesId::Mewtwo: return "Mewtwo"; break;
        case MockmonSpeciesId::Mew: return "Mew"; break;   
        default: return "Unknown mockmon!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const MockmonSpeciesId& speceis)
    {
        os << speciesToStr(speceis);
        return os;
    }
}