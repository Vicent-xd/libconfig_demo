#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

int main(int argc, char **argv)
{
  config_t cfg;
  config_setting_t *setting;
  const char *str;

  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "onvif.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  
    /* Get the store name. 读�~O~V�~E~M置�~V~G件中�~Z~D�~@~\Basic store information:�~@~]信�~A� */
  if(config_lookup_string(&cfg, "name", &str))
    printf("Store name: %s\n\n", str);
  else
    fprintf(stderr, "No 'name' setting in configuration file.\n");
  
/*  if(config_lookup_string(&cfg, "speed", &str))
    printf("Store speed: %s\n\n", str);
  else
    fprintf(stderr, "No 'speed' setting in configuration file.\n");
  */
  /* Output a list of all books in the inventory. */
  setting = config_lookup(&cfg, "camera1.speed");
  if(setting != NULL)
  {
    int count = config_setting_length(setting);
    printf("count:%d\n",count);
    int i;

    //printf("%-30s  %-30s   %-6s  %s\n", "TITLE", "AUTHOR", "PRICE", "QTY");

    for(i = 0; i < count; ++i)
    {
      config_setting_t *speed = config_setting_get_elem(setting, i);

      /* Only output the record if all of the expected fields are present. */
      //const char 
      int minutes, degree;
      //double price;
      //int qty;

      //if(!(config_setting_lookup_string(speed, "minutes", &minutes)
       //    && config_setting_lookup_string(speed, "degree", &degree)))
      if(!(config_setting_lookup_int(speed, "minutes", &minutes)
        && config_setting_lookup_int(speed, "degree", &degree)))
        continue;

      printf("%3d  %3d\n", minutes, degree);
    }
    putchar('\n');
  }
  /* Output a list of all movies in the inventory. */
  setting = config_lookup(&cfg, "camera1.cruise");
  if(setting != NULL)
  {
    unsigned int count = config_setting_length(setting);
    unsigned int i;
    printf("count:%d\n",count);

    //printf("%-30s  %-10s   %-6s  %s\n", "TITLE", "MEDIA", "PRICE", "QTY");
    for(i = 0; i < count; ++i)
    {
      config_setting_t *cruise = config_setting_get_elem(setting, i);

      /* Only output the record if all of the expected fields are present. */
      //const char *title, *media;
      //double price;
      const char* time;
      double x,y,zoom;

      if(!(//config_setting_lookup_string(movie, "title", &title)
           config_setting_lookup_string(cruise, "time", &time)
           && config_setting_lookup_float(cruise, "x", &x)
           && config_setting_lookup_float(cruise, "y", &y)
           && config_setting_lookup_float(cruise, "zoom", &zoom)))
        continue;

      printf("time:%30s x:%6.2f y:%6.2f zoom:%6.2f\n",time, x, y, zoom);
    }
    putchar('\n');
  }

  config_destroy(&cfg);
  return(EXIT_SUCCESS);

}

