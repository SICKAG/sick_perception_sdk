/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCtimezone.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /TSCTCtimezone.
*/
struct TSCTCtimezone
{

  constexpr static const char* variableName = "TSCTCtimezone";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the time zone of the client.
   */
  struct Get
  {
    struct Response
    {
      enum class TSCTCtimezone
      {
        DateLineStandard = 0,
        CoordWorldTime11 = 1,
        Hawaii = 2,
        Alaska = 3,
        California = 4,
        UsaCanada = 5,
        Arizona = 6,
        LaPaz = 7,
        MountainTimeUsa = 8,
        CentralTimeUsa = 9,
        MexicoCity = 10,
        MiddleAmerica = 11,
        Saskatchewan = 12,
        BogotaLima = 13,
        EasternTimeUsa = 14,
        Indiana = 15,
        Caracas = 16,
        Asuncion = 17,
        AtlanticKanada = 18,
        Cuiaba = 19,
        LapazSanjuan = 20,
        Santiago = 21,
        Neufundland = 22,
        Brasilia = 23,
        BuenosAires = 24,
        CayenneFortaleza = 25,
        Groenland = 26,
        Montevideo = 27,
        Salvador = 28,
        CoordWorldTime02 = 29,
        Azoren = 30,
        KapVerde = 31,
        Casablanca = 32,
        DublinLissabonLondon = 33,
        CoordWorldTime = 34,
        MonroviaReykjavik = 35,
        AmsterdamBerlinRom = 36,
        BelgradBudapestPrag = 37,
        BruesselMadridParis = 38,
        SarajevoWarschau = 39,
        WestCentralAfrica = 40,
        Windhuk = 41,
        Johannesburg = 42,
        Amman = 43,
        AthenBukarest = 44,
        Beirut = 45,
        Damascus = 46,
        HararePretoria = 47,
        HelsinkiKiewRiga = 48,
        Istanbul = 49,
        Jerusalem = 50,
        Kairo = 51,
        Kaliningrad = 52,
        Tripolis = 53,
        Bagdad = 54,
        KuwaitRiad = 55,
        Minsk = 56,
        MoskauPetersburg = 57,
        Nairobi = 58,
        Teheran = 59,
        AbuDhabi = 60,
        Baku = 61,
        Eriwan = 62,
        IschewskSamara = 63,
        PortLouis = 64,
        Tiflis = 65,
        Kabul = 66,
        AschgabetTaschkent = 67,
        IslamabadKaratschi = 68,
        Jekaterinburg = 69,
        MumbaiNeudelhi = 70,
        SriJayawardenepura = 71,
        Katmandu = 72,
        Astana = 73,
        Dakka = 74,
        Nowosibirsk = 75,
        Yangon = 76,
        BangkokHanoiJakarta = 77,
        Krasnojarsk = 78,
        Irkutsk = 79,
        KualaLumpurSingapur = 80,
        PekingHongkong = 81,
        Perth = 82,
        Taipeh = 83,
        UlanBator = 84,
        Jakutsk = 85,
        OsakaTokio = 86,
        Seoul = 87,
        Adelaide = 88,
        Darwin = 89,
        Brisbane = 90,
        CanberraSydney = 91,
        GuamPortMoresby = 92,
        Hobart = 93,
        Magadan = 94,
        Wladiwostok = 95,
        SalomonenKaledonien = 96,
        Tschokurdach = 97,
        Anadyr = 98,
        AucklandWellington = 99,
        Fidschi = 100,
        CoordWorldTime12 = 101,
        Nakualofa = 102,
        Samoa = 103,
        Kiritimati = 104,
      };

      Response() = default;

      explicit Response(TSCTCtimezone TSCTCtimezone)
        : _TSCTCtimezone(TSCTCtimezone)
      {}

      TSCTCtimezone _TSCTCtimezone;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the time zone of the client.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class TSCTCtimezone
      {
        DateLineStandard = 0,
        CoordWorldTime11 = 1,
        Hawaii = 2,
        Alaska = 3,
        California = 4,
        UsaCanada = 5,
        Arizona = 6,
        LaPaz = 7,
        MountainTimeUsa = 8,
        CentralTimeUsa = 9,
        MexicoCity = 10,
        MiddleAmerica = 11,
        Saskatchewan = 12,
        BogotaLima = 13,
        EasternTimeUsa = 14,
        Indiana = 15,
        Caracas = 16,
        Asuncion = 17,
        AtlanticKanada = 18,
        Cuiaba = 19,
        LapazSanjuan = 20,
        Santiago = 21,
        Neufundland = 22,
        Brasilia = 23,
        BuenosAires = 24,
        CayenneFortaleza = 25,
        Groenland = 26,
        Montevideo = 27,
        Salvador = 28,
        CoordWorldTime02 = 29,
        Azoren = 30,
        KapVerde = 31,
        Casablanca = 32,
        DublinLissabonLondon = 33,
        CoordWorldTime = 34,
        MonroviaReykjavik = 35,
        AmsterdamBerlinRom = 36,
        BelgradBudapestPrag = 37,
        BruesselMadridParis = 38,
        SarajevoWarschau = 39,
        WestCentralAfrica = 40,
        Windhuk = 41,
        Johannesburg = 42,
        Amman = 43,
        AthenBukarest = 44,
        Beirut = 45,
        Damascus = 46,
        HararePretoria = 47,
        HelsinkiKiewRiga = 48,
        Istanbul = 49,
        Jerusalem = 50,
        Kairo = 51,
        Kaliningrad = 52,
        Tripolis = 53,
        Bagdad = 54,
        KuwaitRiad = 55,
        Minsk = 56,
        MoskauPetersburg = 57,
        Nairobi = 58,
        Teheran = 59,
        AbuDhabi = 60,
        Baku = 61,
        Eriwan = 62,
        IschewskSamara = 63,
        PortLouis = 64,
        Tiflis = 65,
        Kabul = 66,
        AschgabetTaschkent = 67,
        IslamabadKaratschi = 68,
        Jekaterinburg = 69,
        MumbaiNeudelhi = 70,
        SriJayawardenepura = 71,
        Katmandu = 72,
        Astana = 73,
        Dakka = 74,
        Nowosibirsk = 75,
        Yangon = 76,
        BangkokHanoiJakarta = 77,
        Krasnojarsk = 78,
        Irkutsk = 79,
        KualaLumpurSingapur = 80,
        PekingHongkong = 81,
        Perth = 82,
        Taipeh = 83,
        UlanBator = 84,
        Jakutsk = 85,
        OsakaTokio = 86,
        Seoul = 87,
        Adelaide = 88,
        Darwin = 89,
        Brisbane = 90,
        CanberraSydney = 91,
        GuamPortMoresby = 92,
        Hobart = 93,
        Magadan = 94,
        Wladiwostok = 95,
        SalomonenKaledonien = 96,
        Tschokurdach = 97,
        Anadyr = 98,
        AucklandWellington = 99,
        Fidschi = 100,
        CoordWorldTime12 = 101,
        Nakualofa = 102,
        Samoa = 103,
        Kiritimati = 104,
      };

      Request() = default;

      explicit Request(TSCTCtimezone TSCTCtimezone)
        : _TSCTCtimezone(TSCTCtimezone)
      {}

      TSCTCtimezone _TSCTCtimezone;
    };

  }; // struct Post

}; // struct TSCTCtimezone

} // namespace sick::picoScan150::v2_2_1::api::rest
