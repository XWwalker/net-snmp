/*
 * Note: this file originally auto-generated by mib2c 
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/agent/table.h>
#include <net-snmp/agent/table_iterator.h>
#include "nsTransactionTable.h"

/** Initialize the nsTransactionTable table by defining it's contents
   and how it's structured */
void
initialize_table_nsTransactionTable(void)
{
    static oid      nsTransactionTable_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 999, 1, 1 };
    size_t          nsTransactionTable_oid_len =
        OID_LENGTH(nsTransactionTable_oid);
    table_registration_info *table_info;
    handler_registration *my_handler;
    iterator_info *iinfo;

    /*
     * create the table structure itself 
     */
    table_info = SNMP_MALLOC_TYPEDEF(table_registration_info);
    iinfo = SNMP_MALLOC_TYPEDEF(iterator_info);

    /*
     * if your table is read only, it's easiest to change the
     * HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY 
     */
    my_handler = create_handler_registration("nsTransactionTable",
                                             nsTransactionTable_handler,
                                             nsTransactionTable_oid,
                                             sizeof(nsTransactionTable_oid)
                                             / sizeof(oid),
                                             HANDLER_CAN_RONLY);

    if (!my_handler || !table_info || !iinfo)
        return;                 /* mallocs failed */

    /***************************************************
     * Setting up the table's definition
     */
    table_helper_add_index(table_info, ASN_INTEGER);    /* index:
                                                         * nsTransactionID 
                                                         */

    table_info->min_column = 2;
    table_info->max_column = 2;
    iinfo->get_first_data_point =
        nsTransactionTable_get_first_data_point;
    iinfo->get_next_data_point =
        nsTransactionTable_get_next_data_point;
    iinfo->table_reginfo = table_info;

    /***************************************************
     * registering the table with the master agent
     */
    DEBUGMSGTL(("initialize_table_nsTransactionTable",
                "Registering table nsTransactionTable as a table iterator\n"));
    register_table_iterator(my_handler, iinfo);
}

/** Initialzies the nsTransactionTable module */
void
init_nsTransactionTable(void)
{

    /*
     * here we initialize all the tables we're planning on supporting 
     */
    initialize_table_nsTransactionTable();
}

/** returns the first data point within the nsTransactionTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later that will provide you with the data to return in a given
    row.  This could be the same pointer as what my_loop_context is
    set to, or something different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
extern struct agent_snmp_session *agent_delegated_list;

struct variable_list *
nsTransactionTable_get_first_data_point(void **my_loop_context,
                                        void **my_data_context,
                                        struct variable_list
                                        *put_index_data,
                                        iterator_info *iinfo)
{

    struct variable_list *vptr;

    if (!agent_delegated_list)
        return NULL;
    
    *my_loop_context = (void *) agent_delegated_list;
    *my_data_context = (void *) agent_delegated_list;

    vptr = put_index_data;

    snmp_set_var_value(vptr,  (u_char *) &agent_delegated_list->pdu->transid,
                       sizeof(agent_delegated_list->pdu->transid));
    return put_index_data;
}

/** functionally the same as nsTransactionTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it and the return
   my_loop_context->next.  The my_data_context pointer should be set
   to something you need later and the indexes in put_index_data
   updated again. */

struct variable_list *
nsTransactionTable_get_next_data_point(void **my_loop_context,
                                       void **my_data_context,
                                       struct variable_list
                                       *put_index_data,
                                       iterator_info *iinfo)
{

    struct variable_list *vptr;
    struct agent_snmp_session *alist = (struct agent_snmp_session *)
        *my_loop_context;

    if (!alist->next)
        return NULL;

    alist = alist->next;
    
    *my_loop_context = (void *) alist;
    *my_data_context = (void *) alist;

    vptr = put_index_data;

    snmp_set_var_value(vptr, (u_char *) &alist->pdu->transid,
                       sizeof(alist->pdu->transid));
    return put_index_data;
}

/** handles requests for the nsTransactionTable table, if anything
   else needs to be done */
int
nsTransactionTable_handler(mib_handler * handler,
                           handler_registration * reginfo,
                           agent_request_info * reqinfo,
                           request_info * requests)
{

    table_request_info *table_info;
    struct variable_list *var;
    struct agent_snmp_session *asp;
    
    while (requests) {
        var = requests->requestvb;
        if (requests->processed != 0)
            continue;

        /*
         * perform anything here that you need to do.  The requests have
         * already been processed by the master table_dataset handler, but
         * this gives you chance to act on the request in some other way if 
         * need be. 
         */

        /*
         * the following extracts the my_data_context pointer set in the
         * loop functions above.  You can then use the results to help
         * return data for the columns of the nsTransactionTable table in
         * question 
         */
        asp = ( struct agent_snmp_session *)extract_iterator_context(requests);
        if ( asp == NULL) {
            set_request_error(reqinfo, requests, SNMP_NOSUCHINSTANCE);
        }

        /*
         * extracts the information about the table from the request 
         */
        table_info = extract_table_info(requests);

        /*
         * table_info->colnum contains the column number requested 
         */
        /*
         * table_info->indexes contains a linked list of snmp variable
         * bindings for the indexes of the table.  Values in the list have 
         * been set corresponding to the indexes of the request 
         */
        if (table_info == NULL) {
            requests = requests->next;
            continue;
        }

        switch (reqinfo->mode) {
            /*
             * the table_iterator helper should change all GETNEXTs into
             * GETs for you automatically, so you don't have to worry
             * about the GETNEXT case.  Only GETs and SETs need to be
             * dealt with here 
             */
        case MODE_GET:
            switch (table_info->colnum) {

            case COLUMN_NSTRANSACTIONMODE:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *) &asp->mode,
                                         sizeof(asp->mode));
                break;

            default:
                /*
                 * We shouldn't get here 
                 */
                snmp_log(LOG_ERR,
                         "problem encountered in nsTransactionTable_handler: unknown column\n");
            }
            break;

        default:
            snmp_log(LOG_ERR,
                     "problem encountered in nsTransactionTable_handler: unsupported mode\n");
        }
        requests = requests->next;
    }
    return SNMP_ERR_NOERROR;
}
