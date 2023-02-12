//
// Created by Dylan on 10/02/2023.
//

#ifndef CA1_SHIPPING_DATA_STRUCT_H
#define CA1_SHIPPING_DATA_STRUCT_H

#include <string>

using namespace std;
struct shipping_data
    {
        int id;
        char warehouse_block;
        string mode_of_shipment;
        int customer_care_calls;
        int customer_rating;
        int cost_of_the_product;
        int prior_purchases;
        string product_importance;
        char gender;
        int discount_offered;
        int weight_in_gms;
        bool reached_on_time;
    };


#endif //CA1_SHIPPING_DATA_STRUCT_H
